#pragma once

#include <array>
#include <deque>
#include <functional>
#include <thread>
#include <mutex>
#include <asio/error_code.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>

namespace Botcraft
{
#ifdef USE_ENCRYPTION
    class AESEncrypter;
#endif

    class TCP_Com
    {
    public:
        TCP_Com(
            const std::string& address,
            std::function<void(std::vector<unsigned char>)> callback,
            std::function<void()> on_close_callback
        );
        ~TCP_Com();

        void close();

        void SendPacket(const std::vector<unsigned char>& bytes);
#ifdef USE_ENCRYPTION
        void SetEncrypter(const std::shared_ptr<AESEncrypter> encrypter_);
#endif

        const std::string& GetIp() const;
        const unsigned short GetPort() const;

    private:
        void handle_read(const asio::error_code& error, std::size_t bytes_transferred);

        void do_write(const std::vector<unsigned char>& bytes);

        void handle_write(const asio::error_code& error);

        void do_close();

        void SetIPAndPortFromAddress(const std::string& address);


    private:
        // io_context must be declared before socket
        asio::io_context io_context;
        asio::ip::tcp::socket socket;

        std::thread thread_com;

        std::array<unsigned char, 512> read_packet;
        std::vector<unsigned char> input_packet;
        std::deque<std::vector<unsigned char> > output_packet;

        std::function<void(std::vector<unsigned char>)> NewPacketCallback;
        std::mutex mutex_output;

        std::string ip;
        unsigned short port;

#ifdef USE_ENCRYPTION
        std::shared_ptr<AESEncrypter> encrypter;
#endif
        std::function<void()> OnCloseCallback;
        bool close_reported;
    };
} // Botcraft
