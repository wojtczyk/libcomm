#ifndef COMM_UDPSOCKETWIN32_H
#define COMM_UDPSOCKETWIN32_H

#ifdef WIN32 // Build UdpSocketWin32 only if compiled on a Win32 platform

#include <Winsock2.h>
#include "UdpSocket.h"

namespace comm
{

/**
 * @class UdpSocketWin32 UdpSocketWin32.h comm/UdpSocketWin32.h
 * @brief Implementation of the UdpSocket class for Win32 platforms.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * UdpSocketWin32 is the concrete implementation of a udp socket communication
 * under Win32. A programmer should however not call the functions of this class
 * directly but use the UdpSocket class instead since UdpSocket allows
 * operating system indepenedent access.
 */
class UdpSocketWin32 : public comm::UdpSocket
{
private:
	/** @brief Socket address for the connection. */
	struct sockaddr_in server_addr;
	/** @brief Handle for the opened socket */
	int udp_socket;

public:
	UdpSocketWin32();
	virtual ~UdpSocketWin32();

	static UdpSocketWin32* create();

	virtual void configure(const SocketConfiguration* configuration) throw(std::exception);
	
	virtual void open() throw(std::exception);
	virtual void close() throw(std::exception);
	virtual int send(const std::string& sendbuf) throw(std::exception);
	virtual std::string receive() throw(std::exception);
	virtual int dataAvailable();
};

};

#endif // WIN32

#endif //COMM_UDPSOCKETWIN32_H
