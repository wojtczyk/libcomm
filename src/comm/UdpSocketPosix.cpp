#ifdef POSIX // Build UdpSocketPosix only if compiled on a Posix platform

#include <exception>
#include <stdexcept>
#include <arpa/inet.h>
#include <unistd.h>
#include "SocketConfiguration.h"
#include "UdpSocketPosix.h"

using namespace std;

namespace comm
{

/**
 * @brief Does nothing.
 */
UdpSocketPosix::UdpSocketPosix()
{
}

/**
 * @brief Does nothing.
 */
UdpSocketPosix::~UdpSocketPosix()
{
}

/**
 * @brief Creates an instance of the UdpSocketPosix class.
 * @return A pointer to the created object.
 * 
 * The caller should make sure, that the memory of the returned object is freed
 * once it is no longer needed, by calling delete.
 */
UdpSocketPosix* UdpSocketPosix::create()
{
	return new UdpSocketPosix();
};

/**
 * @brief Store the configuration for this socket communication object
 * @param configuration The configuration parameters for the udp socket.
 * 
 * This method actually only stores the configuration parameters.
 */
void UdpSocketPosix::configure(const SocketConfiguration* configuration)
	throw(std::exception)
{
	this->socketConfiguration = *configuration;
};

/**
 * @brief Evaluates the configuration object and opens the udp socket.
 */
void UdpSocketPosix::open() throw(std::exception)
{
	string functionSignature = "int UdpSocketPosix::open()";

	this->udp_socket = socket(PF_INET, SOCK_DGRAM, 0);

	// bind socket
	server_addr.sin_family = PF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = 0;
	if (bind(this->udp_socket, (struct sockaddr*) &this->server_addr,
		sizeof(this->server_addr)) == -1)
	{
		throw runtime_error(functionSignature + " Cannot bind socket");
	};

	// define address of the server
	server_addr.sin_addr.s_addr = inet_addr(this->socketConfiguration.address.c_str());
	server_addr.sin_port = htons(this->socketConfiguration.port);
	
};

/**
 * @brief Closes the socket.
 */
void UdpSocketPosix::close() throw(std::exception)
{
	string functionSignature = "void UdpSocketPosix::close()";
	
	int errcode = ::close(this->udp_socket);
	if (errcode == -1)
	{
		throw runtime_error(functionSignature + " Error while closing socket");
	};
};

/**
 * @brief Sends a string to the udp socket.
 * @param sendbuf The send buffer.
 */
int UdpSocketPosix::send(const std::string& sendbuf) throw(std::exception)
{
	string functionSignature =
		"int UdpSocketPosix::send(const std::string& sendbuf)";

	// send message
	int sent = sendto(this->udp_socket, sendbuf.c_str(), sendbuf.length(), 0,
		(struct sockaddr *) &this->server_addr, sizeof(this->server_addr));

	if (sent == -1)
	{
		string error(functionSignature + " Error while sending request to '" + 
			this->socketConfiguration.address + "'");
		throw runtime_error(error.c_str());
	}
	else
	{
		return sent;
	};
};

/**
 * @brief Read data from the udp socket.
 * @return A string containing the received characters.
 * 
 * This method reads all characters, which are available at the udp socket
 * and returns them in a string.
 */
std::string UdpSocketPosix::receive() throw(std::exception)
{	
	string functionSignature =	"std::string UdpSocketPosix::receive()";

	char recvbuf[1024];
	
	// receive reply from the server
	int length = recvfrom(udp_socket, recvbuf, sizeof(recvbuf) - 1, 0,
		NULL, NULL);
	if (length == -1)
	{
		throw runtime_error(functionSignature + " Error while receiving reply");
	}
	recvbuf[length] = '\0';
	
	return string(recvbuf);
};

/**
 * @brief TODO not implemented
 */
int UdpSocketPosix::dataAvailable()
{
	return 0;
};

};

#endif // POSIX
