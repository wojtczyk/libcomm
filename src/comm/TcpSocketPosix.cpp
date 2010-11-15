#ifdef POSIX // Build TcpSocketPosix only if compiled on a Posix platform

#include <exception>
#include <stdexcept>
#include <arpa/inet.h>
#include <unistd.h>
#include "SocketConfiguration.h"
#include "TcpSocketPosix.h"

#include <iostream>

using namespace std;

namespace comm
{

/**
 * @brief Does nothing.
 */
TcpSocketPosix::TcpSocketPosix()
{
}

/**
 * @brief Does nothing.
 */
TcpSocketPosix::~TcpSocketPosix()
{
}

/**
 * @brief Creates an instance of the TcpSocketPosix class.
 * @return A pointer to the created object.
 * 
 * The caller should make sure, that the memory of the returned object is freed
 * once it is no longer needed, by calling delete.
 */
TcpSocketPosix* TcpSocketPosix::create()
{
	return new TcpSocketPosix();
};

/**
 * @brief Store the configuration for this socket communication object
 * @param configuration The configuration parameters for the tcp socket.
 * 
 * This method actually only stores the configuration parameters.
 */
void TcpSocketPosix::configure(const SocketConfiguration* configuration)
	throw(std::exception)
{
	this->socketConfiguration = *configuration;
};

/**
 * @brief Evaluates the configuration object and opens the tcp socket.
 */
void TcpSocketPosix::open() throw(std::exception)
{
	string functionSignature = "int TcpSocketPosix::open()";

	this->tcp_socket = socket(PF_INET, SOCK_STREAM, 0);

	// connect to socket
	server_addr.sin_family = PF_INET;
	// define address of the server
	server_addr.sin_addr.s_addr = inet_addr(this->socketConfiguration.address.c_str());
	server_addr.sin_port = htons(this->socketConfiguration.port);
	if (connect(this->tcp_socket, (struct sockaddr*) &this->server_addr,
		sizeof(this->server_addr)) == -1)
	{
		throw runtime_error(functionSignature + " Cannot connect to socket");
	};
};

/**
 * @brief Closes the socket.
 */
void TcpSocketPosix::close() throw(std::exception)
{
	string functionSignature = "void TcpSocketPosix::close()";
	
	int errcode = ::close(this->tcp_socket);
	if (errcode == -1)
	{
		throw runtime_error(functionSignature + " Error while closing socket");
	};
};

/**
 * @brief Sends a string to the tcp socket.
 * @param sendbuf The send buffer.
 */
int TcpSocketPosix::send(const std::string& sendbuf) throw(std::exception)
{
	string functionSignature =
		"int TcpSocketPosix::send(const std::string& sendbuf)";

	cout << "TcpSocketPosix::send() ";
/*
	cout.setf(ios_base::hex, ios_base::basefield);  // set hex as the basefield
	cout.setf(ios_base::showbase);                  // activate showbase
	for (int i = 0; i < sendbuf.length(); i++)
	{
		cout << (int) sendbuf[i] << " ";
	};
*/
	cout << sendbuf;
	cout << endl;

	// send message
	int sent = sendto(this->tcp_socket, sendbuf.c_str(), sendbuf.length(), 0,
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
 * @brief Read data from the tcp socket.
 * @return A string containing the received characters.
 * 
 * This method reads all characters, which are available at the tcp socket
 * and returns them in a string.
 */
std::string TcpSocketPosix::receive() throw(std::exception)
{	
	string functionSignature = "std::string TcpSocketPosix::receive()";

	char recvbuf[1024];
	
	// receive reply from the server
	int length = recvfrom(tcp_socket, recvbuf, sizeof(recvbuf) - 1, 0,
		NULL, NULL);
	if (length == -1)
	{
		throw runtime_error(functionSignature + " Error while receiving reply");
	}
	recvbuf[length] = '\0';

	cout << "TcpSocketPosix::receive() ";
/*
	cout.setf ( ios_base::hex, ios_base::basefield );  // set hex as the basefield
	cout.setf ( ios_base::showbase );                  // activate showbase
	for (int i = 0; i < length; i++)
	{
		cout << (int) recvbuf[i] << " ";
	};
*/
	cout << recvbuf;
	cout << endl;
	
	return string(recvbuf);
};

/**
 * @brief TODO not implemented
 */
int TcpSocketPosix::dataAvailable()
{
	return 0;
};

};

#endif // POSIX
