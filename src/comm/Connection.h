#ifndef COMM_CONNECTION_H
#define COMM_CONNECTION_H

#include <string>

namespace comm
{

class Configuration;

/**
 * @class Connection Connection.h comm/Connection.h
 * @brief Handles a connection to an I/O Device
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * Connection is the base class for specific sort of connections like through
 * a serial port or a tcp socket.
 */	
class Connection
{
public:
	Connection();
	virtual ~Connection();
	
	virtual void open() throw(std::exception) = 0;
	virtual void close() throw(std::exception) = 0;
	virtual int send(const std::string& sendbuf) throw(std::exception) = 0;
	virtual std::string receive() throw(std::exception) = 0;
	virtual int dataAvailable() = 0;
};

};

#endif //COMM_CONNECTION_H
