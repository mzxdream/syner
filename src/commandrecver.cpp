#include "commandrecver.h"

CommandRecver::CommandRecver(int nPort)
    :m_nPort(nPort)
{
}
CommandRecver::CommandRecver(const std::string &strIP, int nPort)
    :m_strIP(strIP)
    ,m_nPort(nPort)
{
}
bool CommandRecver::Init()
{
    if (m_strIP.empty())
    {
	return m_sock.Init() && m_sock.Create(SocketType::UDP) && m_sock.Bind(m_nPort);
    }
    else
    {
	return m_sock.Init() && m_sock.Create(SocketType::UDP) && m_sock.Bind(m_strIP, m_nPort);
    }
}
void CommandRecver::Clear()
{
    m_sock.Clear();
}
void CommandRecver::Recv()
{
    ICommand *pCommand = nullptr;
    char szBuf[COMMAND_MAX_SIZE+1];
    std::string strIP;
    int nPort;
    ssize_t bufLen;
    while (true)
    {
	bufLen = m_sock.RecvFrom(szBuf, COMMAND_MAX_SIZE, strIP, nPort);
	if (bufLen > 0)
	{
	    szBuf[bufLen] = '\0';
	    std::stringstream ss;
	    ss << szBuf;
	    boost::archive::text_iarchive ia(ss);
	    ia >> pCommand;
	    pCommand->SetSenderAddr(std::move(NetAddr(strIP, nPort)));
	    CommandHandler::Instance().Invoke(pCommand);
	    delete pCommand;
	    pCommand = nullptr;
	}
	boost::this_thread::interruption_point();
    }
}
