#ifndef _MXSOCKET_H_
#define _MXSOCKET_H_

#include <string>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

enum class SocketType{TCP, UDP};
class MxSocket
{
public:
    MxSocket();
    ~MxSocket();
    MxSocket(const MxSocket &) = delete;
    MxSocket& operator= (const MxSocket &) = delete;
    bool Init();
    void Clear();
    bool Create(SocketType);
    void Close();
    int Detach();
    void Attach(int);
    bool Bind(int);
    bool Bind(const std::string &, int);
    ssize_t SendTo(const void *, size_t, const std::string &, int, int = 0);
    ssize_t RecvFrom(void *, size_t, std::string &, int &, int = 0);
    ssize_t RecvFrom(void *, size_t, int = 0);
private:
    int m_sock;
};

#endif
