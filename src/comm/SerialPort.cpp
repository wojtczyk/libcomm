#include <exception>
#include <stdexcept>
#include <string>
#include "SerialPortWin32.h"
#include "SerialPort.h"

using namespace std;

namespace comm
{

/**
 * @brief Does nothing.
 */
SerialPort::SerialPort()
{
}

/**
 * @brief Does nothing.
 */
SerialPort::~SerialPort()
{
}

/**
 * @brief Creates a concrete platform dependant serial communication object.
 * @return Pointer to the created object.
 * 
 * Currently there exists only an implementation for Win32. If this method is
 * called on a different platform, an exception is thrown. The caller is
 * responsible for freeing the memory of the object by calling delete, once the
 * object is no longer needed.
 */
SerialPort* SerialPort::create() throw(std::exception)
{
	string functionSignature = "SerialPort* SerialPort::create()";

	// create operating system dependent Object or throw exception
#ifdef WIN32
	return SerialPortWin32::create();
#else
	throw std::runtime_error(functionSignature +
		" not implemented for this platform. I'm sorry about that.");
#endif // WIN32
};

};
