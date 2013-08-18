#include "udp.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

bool Udp::Create()
{
    m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    return m_sock >= 0;
}
bool Udp::Bind(const std::string &strIP, int nPort)
{
    struct sockaddr_in stAddr;
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = inet_addr(strIP.c_str());
    stAddr.sin_port = htons(nPort);
    return bind(m_sock, (struct sockaddr *)&stAddr, sizeof(stAddr)) >= 0;
}
bool Udp::Bind(int nPort)
{
    struct sockaddr_in stAddr;
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    stAddr.sin_port = htons(nPort);
    return bind(m_sock, (struct sockaddr *)&stAddr, sizeof(stAddr)) >= 0;
}
size_t Udp::SendTo(const void *pData, size_t dataLen, const std::string &strIP, int nPort)
{
    struct sockaddr_in stAddr;
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = inet_addr(strIP.c_str());
    stAddr.sin_port = htons(nPort);
    return sendto(m_sock, pData, dataLen, 0, (struct sockaddr *)&stAddr, sizeof (stAddr));
}
size_t Udp::RecvFrom(void *pData, size_t dataLen, std::string &strIP, int &nPort)
{
    struct sockaddr_in stAddr;
    socklen_t sockLen = sizeof(stAddr);
    size_t ret = recvfrom(m_sock, pData, dataLen, 0, (struct sockaddr *)&stAddr, &sockLen);
    strIP = inet_ntoa(stAddr.sin_addr);
    nPort = ntohs(stAddr.sin_port);
    return ret;
}
size_t Udp::RecvFrom(void *pData, size_t dataLen)
{
    struct sockaddr_in stAddr;
    socklen_t sockLen = sizeof(stAddr);
    return recvfrom(m_sock, pData, dataLen, 0, (struct sockaddr *)&stAddr, &sockLen);
}
void Udp::Close()
{
    close(m_sock);
}
