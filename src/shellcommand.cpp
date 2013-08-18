#include "shellcommand.h"
#include <iostream>
#include <stdio.h>

BOOST_CLASS_EXPORT(ShellCommand)

ShellCommand::ShellCommand(const std::string &strCmd)
{
    m_strCmd = strCmd;
}
std::string ShellCommand::GetClassName() const
{
    return "ShellCommand";
}
ICommand* ShellCommand::Clone() const
{
    return new ShellCommand(*this);
}
const std::string& ShellCommand::GetCmd() const
{
    return m_strCmd;
}
void ShellCommand::SetCmd(const std::string &strCmd)
{
    m_strCmd = strCmd;
}
