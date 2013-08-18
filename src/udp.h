#ifndef _UDP_H_
#define _UDP_H_

#include <string>

class Udp
{
public:
    Udp() = default;
    ~Udp() = default;
    Udp(const Udp &) = default;
    Udp& operator=(const Udp &) = default;
public:
    bool Create();
    bool Bind(const std::string &, int);
    bool Bind(int);
    size_t SendTo(const void *, size_t, const std::string &, int);
    size_t RecvFrom(void *, size_t, std::string &, int &);
    size_t RecvFrom(void *, size_t);
    void Close();
private:
    int m_sock;
};

#endif
