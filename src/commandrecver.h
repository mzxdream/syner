#ifndef _COMMANDRECVER_H_
#define _COMMANDRECVER_H_

#include "icommand.h"
#include "netaddr.h"
#include "mxsocket.h"
#include "commandhandler.h"

#define COMMAND_MAX_SIZE 4096

class CommandRecver
{
public:
    explicit CommandRecver(int);
    explicit CommandRecver(const std::string &, int);
    ~CommandRecver() = default;
    CommandRecver(const CommandRecver &) = delete;
    CommandRecver& operator=(const CommandRecver &) = delete;
public:
    bool Init();
    void Clear();
    void Recv();
private:
    MxSocket m_sock;
    std::string m_strIP;
    int m_nPort;
};

#endif
