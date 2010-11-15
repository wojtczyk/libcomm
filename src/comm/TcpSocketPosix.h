#ifndef COMM_TCPSOCKETPOSIX_H
#define COMM_TCPSOCKETPOSIX_H

#ifdef POSIX // Build TcpSocketPosix only if compiled on a Posix platform

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "TcpSocket.h"

namespace comm
{

/**
 * @class TcpSocketPosix TcpSocketPosix.h comm/TcpSocketPosix.h
 * @brief Implementation of the TcpSocket class for Posix platforms.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * TcpSocketPosix is the concrete implementation of a tcp socket communication
 * on Posix systems. A programmer should however not call the functions of this
 * class directly but use the TcpSocket class instead since TcpSocket allows
 * operating system indepenedent access.
 */
class TcpSocketPosix : public comm::TcpSocket
{
private:
	/** @brief Socket address for the connection. */
	struct sockaddr_in server_addr;
	/** @brief Handle for the opened socket */
	int tcp_socket;

public:
	TcpSocketPosix();
	virtual ~TcpSocketPosix();

	static TcpSocketPosix* create();

	virtual void configure(const SocketConfiguration* configuration) throw(std::exception);
	
	virtual void open() throw(std::exception);
	virtual void close() throw(std::exception);
	virtual int send(const std::string& sendbuf) throw(std::exception);
	virtual std::string receive() throw(std::exception);
	virtual int dataAvailable();
};

};

#endif // POSIX

#endif //COMM_TCPSOCKETPOSIX_H
