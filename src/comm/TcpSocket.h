#ifndef COMM_TCPSOCKET_H
#define COMM_TCPSOCKET_H

#include "Socket.h"

namespace comm
{

/**
 * @class TcpSocket TcpSocket.h comm/TcpSocket.h
 * @brief Base class for communication classes via TCP.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * TcpSocket is the operating system independent base class for tcp 
 * communication classes. Its static method create() is supposed to be used to
 * create a tcp socket for the concrete platform, so a programmer doesn't
 * need to take care of the different operating systems.
 */
class TcpSocket : public comm::Socket
{
public:
	TcpSocket();
	virtual ~TcpSocket();
	
	static TcpSocket* create() throw(std::exception);
};

};

#endif //COMM_TCPSOCKET_H
