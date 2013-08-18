#ifndef _COMMANDSENDER_H_
#define _COMMANDSENDER_H_

#include "icommand.h"
#include "netaddr.h"
#include "mxsocket.h"

class CommandSender
{
private:
    CommandSender();
    ~CommandSender() = default;
    CommandSender(const CommandSender &) = delete;
    CommandSender& operator=(const CommandSender &) = delete;
public:
    static CommandSender& Instance();
    bool Init();
    void Clear();
    ssize_t Send(const ICommand *);
private:
    MxSocket m_sock;
    unsigned m_uPackageID;
};

#endif
