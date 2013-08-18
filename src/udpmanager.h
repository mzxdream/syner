#ifndef _UDPMANAGER_H_
#define _UDPMANAGER_H_

class UdpManager
{
private:
    UdpManager() = default;
    ~UdpManager() = default;
    UdpManager(const UdpManager &) = delete;
    UdpManager& operator=(const UdpManager &) = delete;
public:
    static UdpManager& Instance();
};

#endif
