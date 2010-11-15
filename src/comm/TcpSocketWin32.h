#ifndef COMM_TCPSOCKETWIN32_H
#define COMM_TCPSOCKETWIN32_H

#ifdef WIN32 // Build TcpSocketWin32 only if compiled on a Win32 platform

#include <Winsock2.h>
#include "TcpSocket.h"

namespace comm
{

/**
 * @class TcpSocketWin32 TcpSocketWin32.h comm/TcpSocketWin32.h
 * @brief Implementation of the TcpSocket class for Win32 platforms.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * TcpSocketWin32 is the concrete implementation of a tcp socket communication
 * under Win32. A programmer should however not call the functions of this class
 * directly but use the TcpSocket class instead since TcpSocket allows
 * operating system indepenedent access.
 */
class TcpSocketWin32 : public comm::TcpSocket
{
private:
	/** @brief Socket address for the connection. */
	struct sockaddr_in server_addr;
	/** @brief Handle for the opened socket */
	int tcp_socket;

public:
	TcpSocketWin32();
	virtual ~TcpSocketWin32();

	static TcpSocketWin32* create();

	virtual void configure(const SocketConfiguration* configuration) throw(std::exception);
	
	virtual void open() throw(std::exception);
	virtual void close() throw(std::exception);
	virtual int send(const std::string& sendbuf) throw(std::exception);
	virtual std::string receive() throw(std::exception);
	virtual int dataAvailable();
};

};

#endif // WIN32

#endif //COMM_TCPSOCKETWIN32_H
