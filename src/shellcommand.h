#ifndef _SHELLCOMMAND_H_
#define _SHELLCOMMAND_H_

#include "icommand.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>

class ShellCommand
    :public ICommand
{
public:
    ShellCommand() = default;
    explicit ShellCommand(const std::string &);
    ~ShellCommand() = default;
    ShellCommand(const ShellCommand &) = default;
    ShellCommand& operator=(const ShellCommand &) = default;
public:
    std::string GetClassName() const override;
    ICommand* Clone() const override;
public:
    const std::string& GetCmd() const;
    void SetCmd(const std::string &);
private:
    std::string m_strCmd;
private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
	{
	    ar & boost::serialization::base_object<ICommand>(*this);
	    ar & m_strCmd;
	}
};

#endif
