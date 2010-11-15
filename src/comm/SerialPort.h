#ifndef COMM_SERIALPORT_H
#define COMM_SERIALPORT_H

#include "Connection.h"
#include "SerialConfiguration.h"

namespace comm
{
class SerialConfiguration;

/**
 * @class SerialPort SerialPort.h comm/SerialPort.h
 * @brief Base class for communication classes via serial port.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * SerialPort is the operating system independent base class for serial 
 * communication classes. Its static method create() is supposed to be used to
 * create a serial communication object for the concrete platform, so a 
 * programmer doesn't need to take care of the different operating systems.
 */	
class SerialPort :public Connection
{
protected:
	/** @brief Stores the configuration for this serial communication object. */
	SerialConfiguration serialConfiguration;
	
public:
	SerialPort();
	virtual ~SerialPort();
	
	/** 
	 * @brief Sets the serial port properties.
	 * @param configuration The settings for the serial port.
	 */
	virtual void configure(const SerialConfiguration* configuration)
		throw(std::exception) = 0;

	static SerialPort* create() throw(std::exception);
};

};

#endif //COMM_SERIALPORT_H
