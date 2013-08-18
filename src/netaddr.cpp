#include "netaddr.h"

size_t hash_value(const NetAddr &addr)
{
    size_t seed = 0;
    boost::hash_combine(seed, boost::hash_value(addr.m_strIP));
    boost::hash_combine(seed, boost::hash_value(addr.m_nPort));
    return seed;
}
NetAddr::NetAddr(const std::string &strIP, int nPort)
{
    m_strIP = strIP;
    m_nPort = nPort;
}
bool NetAddr::operator==(const NetAddr &addr) const
{
    return m_nPort == addr.m_nPort && m_strIP == addr.m_strIP;
}
const std::string& NetAddr::GetIP() const
{
    return m_strIP;
}
void NetAddr::SetIP(const std::string &strIP)
{
    m_strIP = strIP;
}
int NetAddr::GetPort() const
{
    return m_nPort;
}
void NetAddr::SetPort(int nPort)
{
    m_nPort = nPort;
}
