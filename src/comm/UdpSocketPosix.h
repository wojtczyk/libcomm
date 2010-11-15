#ifndef COMM_UDPSOCKETPOSIX_H
#define COMM_UDPSOCKETPOSIX_H

#ifdef POSIX // Build UdpSocketPosix only if compiled on a Posix platform

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "UdpSocket.h"

namespace comm
{

/**
 * @class UdpSocketPosix UdpSocketPosix.h comm/UdpSocketPosix.h
 * @brief Implementation of the UdpSocket class for Posix platforms.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * UdpSocketPosix is the concrete implementation of a udp socket communication
 * on Posix systems. A programmer should however not call the functions of this
 * class directly but use the UdpSocket class instead since UdpSocket allows
 * operating system indepenedent access.
 */
class UdpSocketPosix : public comm::UdpSocket
{
private:
	/** @brief Socket address for the connection. */
	struct sockaddr_in server_addr;
	/** @brief Handle for the opened socket */
	int udp_socket;

public:
	UdpSocketPosix();
	virtual ~UdpSocketPosix();

	static UdpSocketPosix* create();

	virtual void configure(const SocketConfiguration* configuration) throw(std::exception);
	
	virtual void open() throw(std::exception);
	virtual void close() throw(std::exception);
	virtual int send(const std::string& sendbuf) throw(std::exception);
	virtual std::string receive() throw(std::exception);
	virtual int dataAvailable();
};

};

#endif // POSIX

#endif //COMM_UDPSOCKETPOSIX_H
