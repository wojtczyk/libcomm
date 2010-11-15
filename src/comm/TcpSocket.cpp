#include <exception>
#include <stdexcept>
#include <string>
#include "SocketConfiguration.h"
#include "TcpSocketWin32.h"
#include "TcpSocketPosix.h"
#include "TcpSocket.h"

using namespace std;

namespace comm
{

/**
 * @brief Does nothing.
 */
TcpSocket::TcpSocket()
{
}

/**
 * @brief Does nothing.
 */
TcpSocket::~TcpSocket()
{
}

/**
 * @brief Creates a concrete platform dependant tcp communication object.
 * @return Pointer to the created object.
 * 
 * The current implementation covers Win32 and Posix sockets. If this method is
 * called on a different platform, an exception is thrown. The caller is
 * responsible for freeing the memory of the object by calling delete, once the
 * object is no longer needed.
 */
TcpSocket* TcpSocket::create() throw(std::exception)
{
	string functionSignature = "TcpSocket* TcpSocket::create()";

	// create operating system dependent Object or throw exception
#ifdef WIN32
	return TcpSocketWin32::create();
#elif POSIX
	return TcpSocketPosix::create();
#else
	throw std::runtime_error(functionSignature +
		" not implemented for this platform. I'm sorry about that.");
#endif // WIN32
};


};
