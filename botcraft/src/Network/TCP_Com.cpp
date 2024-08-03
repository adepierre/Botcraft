#include <functional>
#include <asio/connect.hpp>
#include <asio/write.hpp>
#include <asio/ip/udp.hpp>

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
    TCP_Com::TCP_Com(const std::string& address,
        std::function<void(const std::vector<unsigned char>&)> callback)
        : socket(io_service), initialized(false)
    {
        NewPacketCallback = callback;

        SetIPAndPortFromAddress(address);

        asio::ip::tcp::resolver resolver(io_service);
        asio::ip::tcp::resolver::query query(ip, std::to_string(port));
        asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
        LOG_INFO("Trying to connect to " << ip << ":" << port);
        asio::async_connect(socket, iterator,
            std::bind(&TCP_Com::handle_connect, this,
            std::placeholders::_1));

        thread_com = std::thread([&] { io_service.run(); });
        Logger::GetInstance().RegisterThread(thread_com.get_id(), "NetworkIOService");
    }

    TCP_Com::~TCP_Com()
    {
        if (thread_com.joinable())
        {
            Logger::GetInstance().UnregisterThread(thread_com.get_id());
            thread_com.join();
        }
    }

    bool TCP_Com::IsInitialized() const
    {
        return initialized;
    }

    void TCP_Com::SendPacket(const std::vector<unsigned char>& msg)
    {
        std::vector<unsigned char> sized_packet;
        sized_packet.reserve(msg.size() + 5);
        ProtocolCraft::WriteData<ProtocolCraft::VarInt>(static_cast<int>(msg.size()), sized_packet);
        sized_packet.insert(sized_packet.end(), msg.begin(), msg.end());

#ifdef USE_ENCRYPTION
        if (encrypter != nullptr)
        {
            std::vector<unsigned char> encrypted = encrypter->Encrypt(sized_packet);
            io_service.post(std::bind(&TCP_Com::do_write, this, encrypted));
        }
        else
        {
            io_service.post(std::bind(&TCP_Com::do_write, this, sized_packet));
        }
#else
        io_service.post(std::bind(&TCP_Com::do_write, this, sized_packet));
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
        io_service.post(std::bind(&TCP_Com::do_close, this));
    }

    void TCP_Com::handle_connect(const asio::error_code& error)
    {
        if (!error)
        {
            LOG_INFO("Connection to server established.");
            initialized = true;
            socket.async_read_some(asio::buffer(read_msg.data(), read_msg.size()),
                std::bind(&TCP_Com::handle_read, this,
                std::placeholders::_1, std::placeholders::_2));
        }
        else
        {
            LOG_ERROR("Error when connecting to server. Error code :" << error);
        }
    }

    void TCP_Com::handle_read(const asio::error_code& error, std::size_t bytes_transferred)
    {
        if (!error)
        {
#ifdef USE_ENCRYPTION
            if (encrypter != nullptr)
            {
                std::vector<unsigned char> decrypted(bytes_transferred);
                std::copy_n(read_msg.begin(), bytes_transferred, decrypted.data());
                decrypted = encrypter->Decrypt(decrypted);
                for (int i = 0; i < decrypted.size(); ++i)
                {
                    input_msg.push_back(decrypted[i]);
                }
            }
            else
            {
                for (int i = 0; i < bytes_transferred; ++i)
                {
                    input_msg.push_back(read_msg[i]);
                }
            }
#else
            for (int i = 0; i < bytes_transferred; ++i)
            {
                input_msg.push_back(read_msg[i]);
            }
#endif

            while (input_msg.size() != 0)
            {
                std::vector<unsigned char>::const_iterator read_iter = input_msg.begin();
                size_t max_length = input_msg.size();
                int packet_length;
                try
                {
                    packet_length = ProtocolCraft::ReadData<ProtocolCraft::VarInt>(read_iter, max_length);
                }
                catch (const std::runtime_error)
                {
                    break;
                }
                const int bytes_read = static_cast<int>(std::distance<std::vector<unsigned char>::const_iterator>(input_msg.begin(), read_iter));
                std::vector<unsigned char> data_packet;

                if (packet_length > 0 && input_msg.size() >= bytes_read + packet_length)
                {
                    data_packet = std::vector<unsigned char>(input_msg.begin() + bytes_read, input_msg.begin() + bytes_read + packet_length);

                    NewPacketCallback(data_packet);
                    input_msg.erase(input_msg.begin(), input_msg.begin() + bytes_read + packet_length);
                }
                else
                {
                    break;
                }
            }

            socket.async_read_some(asio::buffer(read_msg.data(), read_msg.size()),
                std::bind(&TCP_Com::handle_read, this,
                std::placeholders::_1, std::placeholders::_2));
        }
        else
        {
            do_close();
        }
    }

    void TCP_Com::do_write(const std::vector<unsigned char>& msg)
    {
        mutex_output.lock();
        bool write_in_progress = !output_msg.empty();
        output_msg.push_back(msg);
        mutex_output.unlock();

        if (!write_in_progress)
        {
            asio::async_write(socket,
                asio::buffer(output_msg.front().data(),
                output_msg.front().size()),
                std::bind(&TCP_Com::handle_write, this,
                std::placeholders::_1));
        }
    }

    void TCP_Com::handle_write(const asio::error_code& error)
    {
        if (!error)
        {
            mutex_output.lock();
            output_msg.pop_front();
            mutex_output.unlock();

            if (!output_msg.empty())
            {
                asio::async_write(socket,
                    asio::buffer(output_msg.front().data(),
                    output_msg.front().size()),
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
        socket.close();
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
        LOG_INFO("Performing SRV DNS lookup on " << "_minecraft._tcp." << address << " to find an endpoint");
        asio::ip::udp::socket udp_socket(io_service);

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
        question.SetNameLabels(Utilities::SplitString("_minecraft._tcp." + address, '.'));
        query.SetQuestions({ question });

        // Write the request and send it to google DNS
        std::vector<unsigned char> encoded_query;
        query.Write(encoded_query);
        udp_socket.open(asio::ip::udp::v4());
        asio::ip::udp::endpoint endpoint(asio::ip::address::from_string("8.8.8.8"), 53);
        udp_socket.send_to(asio::buffer(encoded_query), endpoint);

        // Wait for the answer
        std::vector<unsigned char> answer_buffer(512);
        asio::ip::udp::endpoint sender_endpoint;
        const size_t len = udp_socket.receive_from(asio::buffer(answer_buffer), sender_endpoint);

        ProtocolCraft::ReadIterator iter = answer_buffer.begin();
        size_t remaining = len;

        // Read answer
        DNSMessage answer;
        answer.Read(iter, remaining);

        // If there is an answer and it's a SRV one (as it should be)
        if (answer.GetNumberAnswer() > 0
            && answer.GetAnswers()[0].GetTypeCode() == 0x21)
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

        // If we are here either the port was given or the SRV failed
        // In both cases we need to assume the given address is the correct one
        port = (port == 0) ? 25565 : port;
        ip = addressOnly;
    }
} //Botcraft
