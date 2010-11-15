#include <exception>
#include <stdexcept>
#include <string>
#include "SocketConfiguration.h"
#include "UdpSocketWin32.h"
#include "UdpSocketPosix.h"
#include "UdpSocket.h"

using namespace std;

namespace comm
{

/**
 * @brief Does nothing.
 */
UdpSocket::UdpSocket()
{
}

/**
 * @brief Does nothing.
 */
UdpSocket::~UdpSocket()
{
}

/**
 * @brief Creates a concrete platform dependant udp communication object.
 * @return Pointer to the created object.
 * 
 * The current implementation covers Win32 and Posix sockets. If this method is
 * called on a different platform, an exception is thrown. The caller is
 * responsible for freeing the memory of the object by calling delete, once the
 * object is no longer needed.
 */
UdpSocket* UdpSocket::create() throw(std::exception)
{
	string functionSignature = "UdpSocket* UdpSocket::create()";

	// create operating system dependent Object or throw exception
#ifdef WIN32
	return UdpSocketWin32::create();
#elif POSIX
	return UdpSocketPosix::create();
#else
	throw std::runtime_error(functionSignature +
		" not implemented for this platform. I'm sorry about that.");
#endif // WIN32
};


};
