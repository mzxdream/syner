#include "shellcommand.h"
#include "commandhandler.h"
#include <iostream>
#include "commandrecver.h"

class Tmp
    :public boost::signals2::trackable
{
public:
    void ReceiveShellCommand(const ICommand *pCommand)
	{
	    const ShellCommand *pShell = dynamic_cast<const ShellCommand *>(pCommand);
	    if (!pShell)
	    {
		return;
	    }
	    std::cout << pShell->GetCmd() << std::endl;
	}
};

int main(int argc, char *argv[])
{
    Tmp* tmp = new Tmp();
    CommandHandler::Instance().Init();
    CommandHandler::Instance().Connect("ShellCommand", &Tmp::ReceiveShellCommand, tmp);
    CommandRecver recver("127.0.0.1", 8101);

    do
    {
	if (!recver.Init())
	{
	    break;
	}
	boost::thread recvThread(boost::bind(&CommandRecver::Recv, &recver));
	boost::this_thread::sleep(boost::posix_time::seconds(100));
	recvThread.interrupt();
	recvThread.join();
	recver.Clear();
    } while(false);

    CommandHandler::Instance().Clear();
    return 0;
}
