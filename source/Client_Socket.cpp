#include <Client_Socket.h>

#include <L_Debug/L_Debug.h>

#include <Net_Engine.h>

using namespace LNet;


Client_Socket::Client_Socket(unsigned int _buffer_size)
{
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (m_socket == INVALID_SOCKET)
    {
        L_LOG(Net_Engine::instance().log_level(), "error while creating a client socket");
        L_ASSERT(m_socket != INVALID_SOCKET);
        return;
    }

    L_LOG(Net_Engine::instance().log_level(), "successfuly created client socket");

    m_buffer_size = _buffer_size;
    m_buffer = new char[m_buffer_size];
}

Client_Socket::~Client_Socket()
{
    delete[] m_buffer;
    closesocket(m_socket);
}



void Client_Socket::connect(const std::string& _ip, int _port)
{
    m_server_ip = _ip;
    m_port = _port;

    m_server_address.sin_family = AF_INET;
    m_server_address.sin_port = htons(_port);
    inet_pton(AF_INET, _ip.c_str(), &m_server_address.sin_addr);
}


bool Client_Socket::send(const std::string& _message)
{
    int sent = sendto(m_socket, _message.c_str(), _message.length(), 0, (sockaddr*)&m_server_address, sizeof(m_server_address));

    if (sent != SOCKET_ERROR && sent > 0)
        return true;

    L_LOG(Net_Engine::instance().log_level(), "error sending a message to ip:[" + m_server_ip + "], port:[" + std::to_string(m_port) + "]");
    return false;
}

bool Client_Socket::send(const Package& _package)
{
    int sent = sendto(m_socket, _package.raw_data(), _package.raw_data_size(), 0, (sockaddr*)&m_server_address, sizeof(m_server_address));

    if (sent != SOCKET_ERROR && sent > 0)
        return true;

    L_LOG(Net_Engine::instance().log_level(), "error sending a message to ip:[" + m_server_ip + "], port:[" + std::to_string(m_port) + "]");
    return false;
}

Package Client_Socket::receive()
{
    sockaddr_in from_address;
    int sockaddr_size = sizeof(from_address);

    int received = recvfrom(m_socket, m_buffer, m_buffer_size - 1, 0, (sockaddr*)&from_address, &sockaddr_size);

    if (received > 0)
    {
        Package result;
        result.append_data(m_buffer, received);
        return result;
    }

    L_LOG(Net_Engine::instance().log_level(), "error receiving a message from ip:[" + m_server_ip + "], port:[" + std::to_string(m_port) + "]");

    return { };
}
