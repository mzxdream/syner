#include "commandhandler.h"

CommandHandler::CommandHandler()
{
}
CommandHandler& CommandHandler::Instance()
{
    static CommandHandler handler;
    return handler;
}
bool CommandHandler::Init()
{
    return true;
}
void CommandHandler::Clear()
{
    WRITELOCK writeLock(m_rwMutex);
    m_sigMap.clear();
}
CommandHandler::SIGCONN CommandHandler::Connect(const std::string &strClassName, void (*pFunc)(const ICommand *))
{
    WRITELOCK writeLock(m_rwMutex);
    return m_sigMap[strClassName].connect(pFunc);
}

CommandHandler::SIGCONN CommandHandler::Connect(const std::string &strClassName, int nIndex, void (*pFunc)(const ICommand *))
{
    WRITELOCK writeLock(m_rwMutex);
    return m_sigMap[strClassName].connect(nIndex, pFunc);
}
bool CommandHandler::Disconnect(const std::string &strClassName, void (*pFunc)(const ICommand *))
{
    READLOCK readLock(m_rwMutex);
    SIGPUNMAP_IT iter = m_sigMap.find(strClassName);
    if (iter != m_sigMap.end())
    {
	iter->second->disconnect(pFunc);
	return true;
    }
    return false;
}
bool CommandHandler::Disconnect(const std::string &strClassName)
{
    READLOCK readLock(m_rwMutex);
    SIGPUNMAP_IT iter = m_sigMap.find(strClassName);
    if (iter != m_sigMap.end())
    {
	iter->second->disconnect_all_slots();
	return true;
    }
    return false;
}

void CommandHandler::Invoke(const ICommand *pCommand)
{
    READLOCK readLock(m_rwMutex);
    SIGPUNMAP_IT iter = m_sigMap.find(pCommand->GetClassName());
    if (iter != m_sigMap.end())
    {
	(*(iter->second))(pCommand);
    }
}
