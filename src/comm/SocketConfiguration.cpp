#include <string>
#include "SocketConfiguration.h"

namespace comm
{

/**
 * @brief Creates and initializes a SocketConfiguration object.
 * @param address A string containing the host address in a common format.
 * @param port An integer identifying the communication port.
 * 
 * Port must be in the range from 0-65535.
 */
SocketConfiguration::SocketConfiguration(const std::string& address, const int port)
{
	this->address = address;
	this->port = port;
}

/**
 * @brief Does nothing.
 */
SocketConfiguration::~SocketConfiguration()
{
}

};
