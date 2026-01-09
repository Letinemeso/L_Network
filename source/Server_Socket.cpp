#include <Server_Socket.h>

#include <L_Debug/L_Debug.h>

#include <Net_Engine.h>

using namespace LNet;


Server_Socket::Server_Socket(int _port, unsigned int _buffer_size)
{
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == INVALID_SOCKET)
        L_LOG(Net_Engine::instance().log_level(), "error while creating a server socket");
    L_ASSERT(m_socket != INVALID_SOCKET);

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(_port);

    unsigned int binding_result = bind(m_socket, (sockaddr*)&m_address, sizeof(m_address));
    if(binding_result == SOCKET_ERROR)
    {
        closesocket(m_socket);
        L_LOG(Net_Engine::instance().log_level(), "error while binding a server socket");
        L_ASSERT(binding_result != SOCKET_ERROR);

        return;
    }

    L_LOG(Net_Engine::instance().log_level(), "successfuly created and binded server socket");

    m_buffer_size = _buffer_size;
    m_buffer = new char[m_buffer_size];
}

Server_Socket::~Server_Socket()
{
    delete[] m_buffer;
    closesocket(m_socket);
}



void Server_Socket::send(const std::string& _message, const sockaddr_in& _client)
{
    sendto(m_socket, _message.c_str(), _message.length(), 0, (sockaddr*)&_client, sizeof(_client));
}

Server_Socket::Message Server_Socket::receive()
{
    Message message;

    int client_address_length = sizeof(message.client_address);

    int received = recvfrom(m_socket, m_buffer, m_buffer_size - 1, 0, (sockaddr*)&message.client_address, &client_address_length);

    if (received > 0)
    {
        message.message.resize(received + 1, 0);
        for(unsigned int i = 0; i < received; ++i)
            message.message[i] = m_buffer[i];
        message.message[received] = 0;

        message.received = received;
        return message;
    }

    L_LOG(Net_Engine::instance().log_level(), "server error while receiving a message");

    return message;
}
