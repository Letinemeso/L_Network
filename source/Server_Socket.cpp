#include <Server_Socket.h>

#include <L_Debug/L_Debug.h>

#include <Net_Engine.h>

using namespace LNet;


Server_Socket::Server_Socket(int _port, unsigned int _buffer_size)
{
    Net_Engine::instance();     //  in case winsock is not initialized

    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == INVALID_SOCKET)
        L_LOG(Net_Engine::instance().log_level(), "error while creating a server socket");
    L_ASSERT(m_socket != INVALID_SOCKET);

    sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(_port);

    unsigned int binding_result = bind(m_socket, (sockaddr*)&address, sizeof(address));
    if(binding_result == SOCKET_ERROR)
    {
        closesocket(m_socket);
        L_LOG(Net_Engine::instance().log_level(), "error while binding a server socket");
        L_ASSERT(binding_result != SOCKET_ERROR);

        return;
    }

    m_address.init_address(address);

    L_LOG(Net_Engine::instance().log_level(), "successfuly created and binded server socket");

    m_buffer_size = _buffer_size;
    m_buffer = new char[m_buffer_size];
}

Server_Socket::~Server_Socket()
{
    delete[] m_buffer;
    closesocket(m_socket);
}



void Server_Socket::send(const std::string& _message, const IP_Address& _client)
{
    sendto(m_socket, _message.c_str(), _message.length(), 0, (const sockaddr*)&_client.address(), sizeof(_client.address()));
}

void Server_Socket::send(const Package& _package, const IP_Address& _client)
{
    sendto(m_socket, _package.raw_data(), _package.raw_data_size(), 0, (const sockaddr*)&_client.address(), sizeof(_client.address()));
}

Server_Socket::Message Server_Socket::receive()
{
    Message message;

    if(m_listen_timeout_ms == 0)
        setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, NULL, 0);
    else
        setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&m_listen_timeout_ms, sizeof(m_listen_timeout_ms));

    sockaddr_in address;
    int client_address_length = sizeof(address);

    int received = recvfrom(m_socket, m_buffer, m_buffer_size - 1, 0, (sockaddr*)&address, &client_address_length);

    if (received <= 0)
        return message;

    message.client_address.init_address(address);
    message.package.append_data(m_buffer, received);

    return message;
}
