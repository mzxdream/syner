#include "commandsender.h"
#include "shellcommand.h"
#include <sstream>

CommandSender::CommandSender()
    :m_uPackageID(0)
{
}
CommandSender& CommandSender::Instance()
{
    static CommandSender sender;
    return sender;
}
bool CommandSender::Init()
{
    m_uPackageID = 0;
    return m_sock.Init() && m_sock.Create(SocketType::UDP);
}
void CommandSender::Clear()
{
    m_sock.Clear();
}
ssize_t CommandSender::Send(const ICommand *pCommand)
{
    if (!pCommand)
    {
	return false;
    }
    ICommand *pNewCommand = pCommand->Clone();
    if (!pNewCommand)
    {
	return false;
    }
    //jiasuo
    pNewCommand->SetPackageID(m_uPackageID);
    m_uPackageID++;
    //jiesuo
    
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << pNewCommand;
    std::string strArchive = ss.str();
    const NetAddr& addr = pNewCommand->GetRecverAddr();
    return m_sock.SendTo(strArchive.c_str(), strArchive.length(), addr.GetIP(), addr.GetPort());
}
