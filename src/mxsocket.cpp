#include "mxsocket.h"

MxSocket::MxSocket()
    :m_sock(-1)
{
}
MxSocket::~MxSocket()
{
    Clear();
}
bool MxSocket::Init()
{
    return true;
}
void MxSocket::Clear()
{
    Close();
}
bool MxSocket::Create(SocketType eType)
{
    if (SocketType::UDP == eType)
    {
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    else
    {
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
    }
    return m_sock >= 0;
}
void MxSocket::Close()
{
    if (m_sock >= 0)
    {
	close(m_sock);
	m_sock = -1;
    }
}
int MxSocket::Detach()
{
    int nSock = m_sock;
    m_sock = -1;
    return nSock;
}
void MxSocket::Attach(int nSock)
{
    Close();
    m_sock = nSock;
}
bool MxSocket::Bind(int nPort)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(nPort);
    return bind(m_sock, (struct sockaddr *)&addr, sizeof(addr)) >= 0;
}
bool MxSocket::Bind(const std::string &strIP, int nPort)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(strIP.c_str());
    addr.sin_port = htons(nPort);
    return bind(m_sock, (struct sockaddr *)&addr, sizeof(addr)) >= 0;
}
ssize_t MxSocket::SendTo(const void *pBuf, size_t bufLen, const std::string &strIP, int nPort, int nFlags)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(strIP.c_str());
    addr.sin_port = htons(nPort);
    return sendto(m_sock, pBuf, bufLen, nFlags, (struct sockaddr *)&addr, sizeof (addr));
}
ssize_t MxSocket::RecvFrom(void *pBuf, size_t bufLen, std::string &strIP, int &nPort, int nFlags)
{
    struct sockaddr_in addr;
    socklen_t sockLen = sizeof(addr);
    ssize_t ret = recvfrom(m_sock, pBuf, bufLen, nFlags, (struct sockaddr *)&addr, &sockLen);
    strIP = inet_ntoa(addr.sin_addr);
    nPort = ntohs(addr.sin_port);
    return ret;
}
ssize_t MxSocket::RecvFrom(void *pBuf, size_t bufLen, int nFlags)
{
    struct sockaddr_in addr;
    socklen_t sockLen = sizeof(addr);
    return recvfrom(m_sock, pBuf, bufLen, nFlags, (struct sockaddr *)&addr, &sockLen);
}
