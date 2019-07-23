#pragma once

#include <deque>
#include <thread>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

namespace Botcraft
{
    class TCP_Com
    {
    public:
        TCP_Com(const std::string &ip, const unsigned int port,
            std::function<void(const std::vector<unsigned char>&)> callback);
        ~TCP_Com();

        void close();

        void SendPacket(const std::vector<unsigned char> &msg);

    private:

        void handle_connect(const boost::system::error_code& error);

        void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);

        void do_write(const std::vector<unsigned char> &msg);

        void handle_write(const boost::system::error_code& error);

        void do_close();


    private:
        // io_service must be declared before socket
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket;

        std::thread thread_com;

        std::array<unsigned char, 512> read_msg;
        std::vector<unsigned char> input_msg;
        std::deque<std::vector<unsigned char> > output_msg;

        std::function<void(const std::vector<unsigned char>&)> NewPacketCallback;
        boost::mutex mutex_output;
    };
} // Botcraft