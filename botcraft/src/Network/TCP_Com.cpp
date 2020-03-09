#include <iterator>
#include <iostream>
#include <functional>

#include "botcraft/Network/TCP_Com.hpp"
#include "protocolCraft/BinaryReadWrite.hpp"

#ifdef USE_ENCRYPTION
#include "botcraft/Network/AESEncrypter.hpp"
#endif

namespace Botcraft
{
    TCP_Com::TCP_Com(const std::string &ip, const unsigned int port,
        std::function<void(const std::vector<unsigned char>&)> callback)
        : socket(io_service)
    {
        NewPacketCallback = callback;

        asio::ip::tcp::resolver resolver(io_service);
        asio::ip::tcp::resolver::query query(ip, std::to_string(port));
        asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
        
        asio::async_connect(socket, iterator,
            std::bind(&TCP_Com::handle_connect, this,
            std::placeholders::_1));

        thread_com = std::thread([&] { io_service.run(); });
    }

    TCP_Com::~TCP_Com()
    {
        if (thread_com.joinable())
        {
            thread_com.join();
        }
    }

    void TCP_Com::SendPacket(const std::vector<unsigned char>& msg)
    {
        std::vector<unsigned char> sized_packet;
        ProtocolCraft::WriteVarInt(msg.size(), sized_packet);
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

    void TCP_Com::close()
    {
        io_service.post(std::bind(&TCP_Com::do_close, this));
    }

    void TCP_Com::handle_connect(const asio::error_code& error)
    {
        if (!error)
        {
            std::cout << "Connected to server." << std::endl;
            socket.async_read_some(asio::buffer(read_msg.data(), read_msg.size()),
                std::bind(&TCP_Com::handle_read, this,
                std::placeholders::_1, std::placeholders::_2));
        }
        else
        {
            std::cerr << "Error when connecting to server. Error code :" << error << std::endl;
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
                    packet_length = ProtocolCraft::ReadVarInt(read_iter, max_length);
                }
                catch (const std::runtime_error &e)
                {
                    break;
                }
                int bytes_read = std::distance<std::vector<unsigned char>::const_iterator>(input_msg.begin(), read_iter);
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

    void TCP_Com::do_write(const std::vector<unsigned char> &msg)
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
} //Botcraft