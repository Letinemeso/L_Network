#pragma once

#include <string>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <Package.h>


namespace LNet
{

    class Client_Socket
    {
    private:
        SOCKET m_socket;
        sockaddr_in m_server_address;

        std::string m_server_ip;
        int m_port = 0;

        char* m_buffer = nullptr;
        unsigned int m_buffer_size = 0;

    public:
        Client_Socket(unsigned int _buffer_size);
        ~Client_Socket();

        Client_Socket(const Client_Socket&) = delete;
        Client_Socket(Client_Socket&&) = delete;
        void operator=(const Client_Socket&) = delete;
        void operator=(Client_Socket&&) = delete;

    public:
        void connect(const std::string& _ip, int _port);

        bool send(const std::string& _message);
        bool send(const Package& _package);
        Package receive();

    };

}
