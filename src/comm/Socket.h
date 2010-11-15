#ifndef COMM_SOCKET_H
#define COMM_SOCKET_H

#include "Connection.h"
#include "SocketConfiguration.h"

namespace comm
{

/**
 * @class Socket Socket.h comm/Socket.h
 * @brief Base class for network sockets communication.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 */
class Socket : public comm::Connection
{
protected:
	/** @brief The stored configuration for this socket */
	SocketConfiguration socketConfiguration;
	
public:
	Socket();
	virtual ~Socket();
	
	/** 
	 * @brief Sets the socket properties.
	 * @param configuration The settings for the socket.
	 */
	virtual void configure(const SocketConfiguration* configuration) throw(std::exception) = 0;
};

};

#endif //COMM_SOCKET_H
