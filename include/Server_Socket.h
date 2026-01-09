#pragma once

#include <string>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <Package.h>


namespace LNet
{

    class Server_Socket
    {
    public:
        struct Message
        {
            sockaddr_in client_address;
            Package package;
        };

    private:
        SOCKET m_socket;
        sockaddr_in m_address;

        std::string m_server_ip;
        int m_port = 0;
        unsigned int m_listen_timeout_ms = 0;

        char* m_buffer = nullptr;
        unsigned int m_buffer_size = 0;

    public:
        Server_Socket(int _port, unsigned int _buffer_size);
        ~Server_Socket();

        Server_Socket(const Server_Socket&) = delete;
        Server_Socket(Server_Socket&&) = delete;
        void operator=(const Server_Socket&) = delete;
        void operator=(Server_Socket&&) = delete;

        inline void set_listen_timeout_ms(unsigned int _value) { m_listen_timeout_ms = _value; }

    public:
        void send(const std::string& _message, const sockaddr_in& _client);
        void send(const Package& _package, const sockaddr_in& _client);
        Message receive();

    };

}
