#ifndef COMM_SERIALPORTWIN32_H
#define COMM_SERIALPORTWIN32_H

#ifdef WIN32 // Build SerialPortWin32 only if compiled on a Win32 platform

#include <Windows.h>
#include "SerialPort.h"

namespace comm
{

/**
 * @class SerialPortWin32 SerialPortWin32.h comm/SerialPortWin32.h
 * @brief Implementation of the SerialPort class for Win32 platforms.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * SerialPortWin32 is the concrete implementation of a serial port communication
 * under Win32. A programmer should however not call the functions of this class
 * directly but use the SerialPort class instead since SerialPort allows
 * operating system indepenedent access.
 */
class SerialPortWin32 : public comm::SerialPort
{
private:
	/** @brief The file handle to the serial port. */
	HANDLE portHandle;

public:
	SerialPortWin32();
	virtual ~SerialPortWin32();

	static SerialPort* create() throw(std::exception);

	virtual void configure(const SerialConfiguration* configuration) throw(std::exception);

	virtual void open() throw(std::exception);
	virtual void close() throw(std::exception);
	virtual int send(const std::string& sendbuf) throw(std::exception);
	virtual std::string receive() throw(std::exception);
	virtual int dataAvailable();
};

};

#endif // WIN32

#endif //COMM_SERIALPORTWIN32_H
