#include <chrono>
#include <functional>
#include <optional>
#include <utility>

#include <asio/connect.hpp>
#include <asio/ip/udp.hpp>
#include <asio/write.hpp>

#include "protocolCraft/BinaryReadWrite.hpp"

#include "botcraft/Network/DNS/DNSMessage.hpp"
#include "botcraft/Network/DNS/DNSSrvData.hpp"
#include "botcraft/Network/TCP_Com.hpp"
#ifdef USE_ENCRYPTION
#include "botcraft/Network/AESEncrypter.hpp"
#endif

#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"

namespace Botcraft
{
    TCP_Com::TCP_Com(
        const std::string& address,
        std::function<void(std::vector<unsigned char>)> callback,
        std::function<void()> on_close_callback
    ) : socket(io_context)
    {
        NewPacketCallback = std::move(callback);
        OnCloseCallback = std::move(on_close_callback);
        close_reported = false;

        SetIPAndPortFromAddress(address);

        asio::ip::tcp::resolver resolver(io_context);
        LOG_INFO("Trying to connect to " << ip << ":" << port);
        try
        {
            asio::connect(socket, resolver.resolve(ip, std::to_string(port)));
        }
        catch (const asio::system_error& e)
        {
            LOG_ERROR("Error when connecting to server. Error code :" << e.what());
            throw;
        }
        LOG_INFO("Connection to server established.");

        socket.async_read_some(
            asio::buffer(read_packet.data(), read_packet.size()),
            std::bind(&TCP_Com::handle_read, this, std::placeholders::_1, std::placeholders::_2)
        );

        thread_com = std::thread([this]() {
            Logger::GetInstance().RegisterThread("NetworkIOService");
            io_context.run();
        });
    }

    TCP_Com::~TCP_Com()
    {
        // Prevent a pending read handler from running after the owner is gone.
        io_context.stop();
        if (thread_com.joinable())
        {
            thread_com.join();
        }
    }

    void TCP_Com::SendPacket(const std::vector<unsigned char>& bytes)
    {
        std::vector<unsigned char> sized_packet;
        sized_packet.reserve(bytes.size() + 5);
        ProtocolCraft::WriteData<ProtocolCraft::VarInt>(static_cast<int>(bytes.size()), sized_packet);
        sized_packet.insert(sized_packet.end(), bytes.begin(), bytes.end());

#ifdef USE_ENCRYPTION
        if (encrypter != nullptr)
        {
            std::vector<unsigned char> encrypted = encrypter->Encrypt(sized_packet);
            asio::post(io_context, std::bind(&TCP_Com::do_write, this, encrypted));
        }
        else
        {
            asio::post(io_context, std::bind(&TCP_Com::do_write, this, sized_packet));
        }
#else
        asio::post(io_context, std::bind(&TCP_Com::do_write, this, sized_packet));
#endif
    }

#ifdef USE_ENCRYPTION
    void TCP_Com::SetEncrypter(const std::shared_ptr<AESEncrypter> encrypter_)
    {
        encrypter = encrypter_;
    }
#endif

    const std::string& TCP_Com::GetIp() const
    {
        return ip;
    }

    const unsigned short TCP_Com::GetPort() const
    {
        return port;
    }

    void TCP_Com::close()
    {
        asio::post(io_context, std::bind(&TCP_Com::do_close, this));
    }

    void TCP_Com::handle_read(const asio::error_code& error, std::size_t bytes_transferred)
    {
        if (!error)
        {
#ifdef USE_ENCRYPTION
            if (encrypter != nullptr)
            {
                std::vector<unsigned char> decrypted(bytes_transferred);
                std::copy_n(read_packet.begin(), bytes_transferred, decrypted.data());
                decrypted = encrypter->Decrypt(decrypted);
                for (int i = 0; i < decrypted.size(); ++i)
                {
                    input_packet.push_back(decrypted[i]);
                }
            }
            else
            {
                for (int i = 0; i < bytes_transferred; ++i)
                {
                    input_packet.push_back(read_packet[i]);
                }
            }
#else
            for (int i = 0; i < bytes_transferred; ++i)
            {
                input_packet.push_back(read_packet[i]);
            }
#endif

            while (input_packet.size() != 0)
            {
                std::vector<unsigned char>::const_iterator read_iter = input_packet.begin();
                size_t max_length = input_packet.size();
                int packet_length;
                try
                {
                    packet_length = ProtocolCraft::ReadData<ProtocolCraft::VarInt>(read_iter, max_length);
                }
                catch (const std::runtime_error)
                {
                    break;
                }
                const int bytes_read = static_cast<int>(std::distance<std::vector<unsigned char>::const_iterator>(input_packet.begin(), read_iter));
                std::vector<unsigned char> data_packet;

                if (packet_length > 0 && input_packet.size() >= bytes_read + packet_length)
                {
                    data_packet = std::vector<unsigned char>(input_packet.begin() + bytes_read, input_packet.begin() + bytes_read + packet_length);

                    NewPacketCallback(std::move(data_packet));
                    input_packet.erase(input_packet.begin(), input_packet.begin() + bytes_read + packet_length);
                }
                else
                {
                    break;
                }
            }

            socket.async_read_some(asio::buffer(read_packet.data(), read_packet.size()),
                std::bind(&TCP_Com::handle_read, this,
                std::placeholders::_1, std::placeholders::_2));
        }
        else
        {
            do_close();
        }
    }

    void TCP_Com::do_write(const std::vector<unsigned char>& bytes)
    {
        mutex_output.lock();
        bool write_in_progress = !output_packet.empty();
        output_packet.push_back(bytes);
        mutex_output.unlock();

        if (!write_in_progress)
        {
            asio::async_write(socket,
                asio::buffer(output_packet.front().data(),
                output_packet.front().size()),
                std::bind(&TCP_Com::handle_write, this,
                std::placeholders::_1));
        }
    }

    void TCP_Com::handle_write(const asio::error_code& error)
    {
        if (!error)
        {
            mutex_output.lock();
            output_packet.pop_front();
            mutex_output.unlock();

            if (!output_packet.empty())
            {
                asio::async_write(socket,
                    asio::buffer(output_packet.front().data(),
                    output_packet.front().size()),
                    std::bind(&TCP_Com::handle_write, this,
                    std::placeholders::_1));
            }
        }
        else
        {
            do_close();
        }
    }

    void TCP_Com::do_close()
    {
        if (close_reported)
        {
            return;
        }
        close_reported = true;

        if (socket.is_open())
        {
            asio::error_code ec;
            socket.close(ec);
            if (ec)
            {
                LOG_ERROR("Error closing socket: " << ec.message());
            }
        }

        if (OnCloseCallback)
        {
            OnCloseCallback();
        }
    }

    void TCP_Com::SetIPAndPortFromAddress(const std::string& address)
    {
        std::string addressOnly;

        const std::vector<std::string> splitted_port = Utilities::SplitString(address, ':');
        // address:port format
        if (splitted_port.size() > 1)
        {
            try
            {
                port = std::stoi(splitted_port[1]);
                ip = splitted_port[0];
                return;
            }
            catch (const std::exception&)
            {
                port = 0;
            }
            addressOnly = splitted_port[0];
        }
        // address only format
        else
        {
            addressOnly = address;
            port = 0;
        }

        // If port is unknown we first try a SRV DNS lookup
        LOG_INFO("Performing SRV DNS lookup on " << "_minecraft._tcp." << addressOnly << " to find an endpoint");
        asio::io_context dns_context;
        asio::ip::udp::socket udp_socket(dns_context);

        // Create the query
        DNSMessage query;
        // Random identification
        query.SetIdentification({ 0x42, 0x42 });
        query.SetFlagQR(0);
        query.SetFlagOPCode(0);
        query.SetFlagAA(0);
        query.SetFlagTC(0);
        query.SetFlagRD(1);
        query.SetFlagRA(0);
        query.SetFlagZ(0);
        query.SetFlagRCode(0);
        query.SetNumberQuestion(1);
        query.SetNumberAnswer(0);
        query.SetNumberAuthority(0);
        query.SetNumberAdditionalRR(0);
        DNSQuestion question;
        // SRV type
        question.SetTypeCode(33);
        question.SetClassCode(1);
        question.SetNameLabels(Utilities::SplitString("_minecraft._tcp." + addressOnly, '.'));
        query.SetQuestions({ question });

        // Write the request and send it to DNS4EU
        std::vector<unsigned char> encoded_query;
        query.Write(encoded_query);
        udp_socket.open(asio::ip::udp::v4());
        asio::ip::udp::endpoint endpoint(asio::ip::make_address("86.54.11.100" /* unfiltered DNS4EU server */), 53);
        asio::error_code send_ec;
        udp_socket.send_to(asio::buffer(encoded_query), endpoint, 0, send_ec);
        if (send_ec)
        {
            LOG_WARNING("SRV DNS query could not be sent: " << send_ec.message());
        }
        else
        {
            // Wait for the answer
            std::vector<unsigned char> answer_buffer(512);
            asio::ip::udp::endpoint sender_endpoint;
            std::optional<size_t> len;
            udp_socket.async_receive_from(
                asio::buffer(answer_buffer),
                sender_endpoint,
                [&len](const asio::error_code& ec, const std::size_t n) {
                    if (!ec)
                    {
                        len = n;
                    }
                }
            );
            dns_context.run_for(std::chrono::seconds(2));

            if (len.has_value())
            {
                ProtocolCraft::ReadIterator iter = answer_buffer.begin();
                size_t remaining = len.value();
                // Read answer
                DNSMessage answer;
                answer.Read(iter, remaining);
                // If there is an answer and it's a SRV one (as it should be)
                if (answer.GetNumberAnswer() > 0 && answer.GetAnswers()[0].GetTypeCode() == 0x21)
                {
                    DNSSrvData data;
                    auto iter2 = answer.GetAnswers()[0].GetRData().begin();
                    size_t len2 = answer.GetAnswers()[0].GetRDLength();
                    data.Read(iter2, len2);
                    ip = "";
                    for (int i = 0; i < data.GetNameLabels().size(); ++i)
                    {
                        ip += data.GetNameLabels()[i] + (i == data.GetNameLabels().size() - 1 ? "" : ".");
                    }
                    port = data.GetPort();

                    LOG_INFO("SRV DNS lookup successful!");
                    return;
                }
                LOG_WARNING("SRV DNS lookup failed to find an address");
            }
            else
            {
                LOG_WARNING("SRV DNS lookup timed out");
            }
        }

        // If we are here either the port was given or the SRV failed
        // In both cases we need to assume the given address is the correct one
        port = (port == 0) ? 25565 : port;
        ip = addressOnly;
    }
} //Botcraft
