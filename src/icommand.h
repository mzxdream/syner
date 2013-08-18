#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include "netaddr.h"

class ICommand
{
public:
    ICommand() = default;
    virtual ~ICommand();
    ICommand(const ICommand &) = default;
    ICommand& operator=(const ICommand &) = default;
public:
    virtual std::string GetClassName() const;
    virtual ICommand* Clone() const = 0;
public:
    unsigned GetPackageID() const;
    void SetPackageID(unsigned);
    const NetAddr& GetSenderAddr() const;
    void SetSenderAddr(const NetAddr &);
    const NetAddr& GetRecverAddr() const;
    void SetRecverAddr(const NetAddr &);
private:
    unsigned m_uPackageID;//包编号，发送的时候，添加
    NetAddr m_senderAddr;//发送者地址
    NetAddr m_recverAddr;//接收者地址
private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
	{
	    ar & m_uPackageID;
	    ar & m_senderAddr;
	    ar & m_recverAddr;
	}
};

#endif
