#pragma once

#include <string>

#include <winsock2.h>
#include <ws2tcpip.h>


namespace LNet
{

    class IP_Address
    {
    private:
        sockaddr_in m_address;
        std::string m_address_str;

    public:
        IP_Address();
        IP_Address(const sockaddr_in& _address);

    public:
        void init_address(const sockaddr_in& _address);

    public:
        static std::string address_to_string(const sockaddr_in& _address);

    public:
        inline const sockaddr_in& address() const { return m_address; }
        inline const std::string& address_str() const { return m_address_str; }

    };

}
