#include "icommand.h"

BOOST_SERIALIZATION_ASSUME_ABSTRACT(ICommand)

ICommand::~ICommand()
{
}
std::string ICommand::GetClassName() const
{
    return "ICommand";
}
unsigned int ICommand::GetPackageID() const
{
    return m_uPackageID;
}
void ICommand::SetPackageID(unsigned uPackageID)
{
    m_uPackageID = uPackageID;
}
const NetAddr& ICommand::GetSenderAddr() const
{
    return m_senderAddr;
}
void ICommand::SetSenderAddr(const NetAddr &netAddr)
{
    m_senderAddr = netAddr;
}
const NetAddr& ICommand::GetRecverAddr() const
{
    return m_recverAddr;
}
void ICommand::SetRecverAddr(const NetAddr &netAddr)
{
    m_recverAddr = netAddr;
}
    
