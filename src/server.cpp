#include "shellcommand.h"
#include "commandhandler.h"
#include <iostream>
#include "commandsender.h"

int main(int argc, char *argv[])
{
    std::string strIP("127.0.0.1");
    int nPort = 8101;

    std::string strCmd;
    if (!CommandSender::Instance().Init())
    {
	std::cout << "commandsender init failed" << std::endl;
	return 0;
    }

    while (std::getline(std::cin, strCmd))
    {
	ICommand *pCommand = new ShellCommand(strCmd);
	pCommand->SetRecverAddr(std::move(NetAddr(strIP, nPort)));
	CommandSender::Instance().Send(pCommand);
    }
    CommandSender::Instance().Clear();
    return 0;
}
    
