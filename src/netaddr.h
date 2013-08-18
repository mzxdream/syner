#ifndef _NETADDR_H_
#define _NETADDR_H_

#include <string>
#include <boost/functional/hash.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>

class NetAddr
{
    friend size_t hash_value(const NetAddr &);
public:
    NetAddr() = default;
    explicit NetAddr(const std::string &, int);
    ~NetAddr() = default;
    NetAddr(const NetAddr &) = default;
    NetAddr& operator=(const NetAddr &) = default;
    bool operator==(const NetAddr &) const;
public:
    const std::string& GetIP() const;
    void SetIP(const std::string &strIP);
    int GetPort() const;
    void SetPort(int);
private:
    std::string m_strIP;
    int m_nPort;
private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
	{
	    ar & m_strIP;
	    ar & m_nPort;
	}
};

size_t hash_value(const NetAddr &addr);

#endif
