#ifndef COMM_SOCKETCONFIGURATION_H
#define COMM_SOCKETCONFIGURATION_H

#include <string>
#include "Configuration.h"

namespace comm
{

/**
 * @class SocketConfiguration SocketConfiguration.h comm/SocketConfiguration.h
 * @brief Stores the settings for a socket.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * SocketConfiguration stores the settings, which are needed to configure 
 * the communication via a socket.
 */	
class SocketConfiguration : public comm::Configuration
{
public:
	/** @brief Host address in a common format */
	std::string address;
	/** @brief Port address (0-65535) */
	int port;

public:
	SocketConfiguration(const std::string& address = "127.0.0.1" ,
		const int port = 0);
	virtual ~SocketConfiguration();
};

};

#endif //COMM_SOCKETCONFIGURATION_H
