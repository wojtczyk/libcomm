#ifndef COMM_UDPSOCKET_H
#define COMM_UDPSOCKET_H

#include "Socket.h"

namespace comm
{

/**
 * @class UdpSocket UdpSocket.h comm/UdpSocket.h
 * @brief Base class for communication classes via UDP.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * UdpSocket is the operating system independent base class for udp 
 * communication classes. Its static method create() is supposed to be used to
 * create a udp socket for the concrete platform, so a programmer doesn't
 * need to take care of the different operating systems.
 */
class UdpSocket : public comm::Socket
{
public:
	UdpSocket();
	virtual ~UdpSocket();
	
	static UdpSocket* create() throw(std::exception);
};

};

#endif //COMM_UDPSOCKET_H
