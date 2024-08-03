#pragma once

#include <atomic>
#include <deque>
#include <thread>
#include <mutex>
#include <asio/error_code.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/io_service.hpp>

namespace Botcraft
{
#ifdef USE_ENCRYPTION
    class AESEncrypter;
#endif

    class TCP_Com
    {
    public:
        TCP_Com(const std::string& address,
            std::function<void(const std::vector<unsigned char>&)> callback);
        ~TCP_Com();

        bool IsInitialized() const;

        void close();

        void SendPacket(const std::vector<unsigned char>& msg);
#ifdef USE_ENCRYPTION
        void SetEncrypter(const std::shared_ptr<AESEncrypter> encrypter_);
#endif

        const std::string& GetIp() const;
        const unsigned short GetPort() const;

    private:

        void handle_connect(const asio::error_code& error);

        void handle_read(const asio::error_code& error, std::size_t bytes_transferred);

        void do_write(const std::vector<unsigned char>& msg);

        void handle_write(const asio::error_code& error);

        void do_close();

        void SetIPAndPortFromAddress(const std::string& address);


    private:
        // io_service must be declared before socket
        asio::io_service io_service;
        asio::ip::tcp::socket socket;

        std::thread thread_com;

        std::array<unsigned char, 512> read_msg;
        std::vector<unsigned char> input_msg;
        std::deque<std::vector<unsigned char> > output_msg;

        std::function<void(const std::vector<unsigned char>&)> NewPacketCallback;
        std::mutex mutex_output;

        std::string ip;
        unsigned short port;

#ifdef USE_ENCRYPTION
        std::shared_ptr<AESEncrypter> encrypter;
#endif

        std::atomic<bool> initialized;
    };
} // Botcraft
