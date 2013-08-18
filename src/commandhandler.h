#ifndef _COMMANDHANDLER_H_
#define _COMMANDHANDLER_H_

#include <boost/signals2.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include "icommand.h"
#include <boost/thread.hpp>
#include <boost/thread/shared_mutex.hpp>

class CommandHandler
{
public:
    typedef boost::signals2::signal<void (const ICommand *)> SIGTYPE;
    typedef boost::signals2::connection SIGCONN;
    typedef boost::ptr_unordered_map<std::string, SIGTYPE> SIGPUNMAP;
    typedef SIGPUNMAP::iterator SIGPUNMAP_IT;
    typedef boost::unordered_map<std::string, SIGTYPE> SIGUNMAP;

    typedef boost::shared_mutex RWMUTEX;
    typedef boost::shared_lock<RWMUTEX> READLOCK;
    typedef boost::unique_lock<RWMUTEX> WRITELOCK;
    

    
private:
    CommandHandler();
    ~CommandHandler() = default;
    CommandHandler(const CommandHandler &) = delete;
    CommandHandler& operator= (const CommandHandler &) = delete;
public:
    static CommandHandler& Instance();
    bool Init();
    void Clear();
    SIGCONN Connect(const std::string &, void (*)(const ICommand *));
    template <typename O, typename T>
    SIGCONN Connect(const std::string &, void (T::*)(const ICommand *), O *);
    SIGCONN Connect(const std::string &, int, void (*)(const ICommand *));
    template <typename O, typename T>
    SIGCONN Connect(const std::string &, int, void (T::*)(const ICommand *), O *);
    bool Disconnect(const std::string &, void (*)(const ICommand *));
    template <typename O, typename T>
    bool Disconnect(const std::string &, void (T::*)(const ICommand *), O *);
    bool Disconnect(const std::string &);
    void Invoke(const ICommand *);
private:
    SIGPUNMAP m_sigMap;
    RWMUTEX m_rwMutex;
};


template <typename O, typename T>
CommandHandler::SIGCONN CommandHandler::Connect(const std::string &strClassName, void (T::*pFunc)(const ICommand *), O *pObj)
{
    WRITELOCK writeLock(m_rwMutex);
    return m_sigMap[strClassName].connect(boost::bind(pFunc, pObj, _1));
}
template <typename O, typename T>
CommandHandler::SIGCONN CommandHandler::Connect(const std::string &strClassName, int nIndex, void (T::*pFunc)(const ICommand *), O *pObj)
{
    WRITELOCK writeLock(m_rwMutex);
    return m_sigMap[strClassName].connect(nIndex, boost::bind(pFunc, pObj, _1));
}
template <typename O, typename T>
bool CommandHandler::Disconnect(const std::string &strClassName, void (T::*pFunc)(const ICommand *), O *pObj)
{
    READLOCK readLock(m_rwMutex);
    SIGPUNMAP_IT iter = m_sigMap.find(strClassName);
    if (iter != m_sigMap.end())
    {
	iter->second->disconnect(boost::bind(pFunc, pObj, _1));
	return true;
    }
    return false;
}

#endif
