#pragma once

#include <string>

#include <winsock2.h>
#include <ws2tcpip.h>


namespace LNet
{

    class Client_Socket
    {
    private:
        SOCKET m_socket;
        sockaddr_in m_server_address;

        std::string m_server_ip;
        int m_port = 0;

        bool m_connected = false;

    public:
        Client_Socket();
        ~Client_Socket();

        Client_Socket(const Client_Socket&) = delete;
        Client_Socket(Client_Socket&&) = delete;
        void operator=(const Client_Socket&) = delete;
        void operator=(Client_Socket&&) = delete;

    public:
        inline bool connected() { return m_connected; }

    public:
        void connect(const std::string& _ip, int _port);

        void send(const std::string& _message);
        std::string receive();

    };

}
