#include <Net_Engine.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <L_Debug/L_Debug.h>

#pragma comment(lib, "ws2_32.lib")

using namespace LNet;


Net_Engine::Net_Engine()
{
    WSADATA wsaData;
    unsigned int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
    L_ASSERT(error == 0);
}

Net_Engine::~Net_Engine()
{
    WSACleanup();
}
