#include <IP_Address.h>

#include <L_Debug/L_Debug.h>

#include <Net_Engine.h>

using namespace LNet;

IP_Address::IP_Address()
{

}

IP_Address::IP_Address(const sockaddr_in& _address)
{
    init_address(_address);
}



void IP_Address::init_address(const sockaddr_in& _address)
{
    m_address = _address;
    m_address_str = address_to_string(_address);
}



std::string IP_Address::address_to_string(const sockaddr_in& _address)
{
    char ip_cstr[INET_ADDRSTRLEN];
    const char* result = inet_ntop(AF_INET, &(_address.sin_addr), ip_cstr, INET_ADDRSTRLEN);

    if(result != nullptr)
        return std::string(ip_cstr);

    L_LOG(LNet::Net_Engine::instance().log_level(), "can't extract ip string from address");
    return {};
}
