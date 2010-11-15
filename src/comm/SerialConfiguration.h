#ifndef COMM_SERIALCONFIGURATION_H
#define COMM_SERIALCONFIGURATION_H

#include "Configuration.h"

namespace comm
{

/**
 * @class SerialConfiguration SerialConfiguration.h comm/SerialConfiguration.h
 * @brief Stores the settings for a serial port.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * SerialConfiguration stores the settings, which are needed to configure 
 * the communication via serial port.
 */	
class SerialConfiguration :public comm::Configuration
{

public:
	/** @brief Port address constants. */
	enum Port
	{
		/** @brief COM1: under Windows, /dev/ttyS0 under Linux */
		P0 = 0,
		/** @brief COM2: under Windows, /dev/ttyS1 under Linux */
		P1 = 1,
		/** @brief COM3: under Windows, /dev/ttyS2 under Linux */
		P2 = 2,
		/** @brief COM4: under Windows, /dev/ttyS3 under Linux */
		P3 = 3,
		/** @brief COM5: under Windows, /dev/ttyS4 under Linux */
		P4 = 4,
		/** @brief COM6: under Windows, /dev/ttyS5 under Linux */
		P5 = 5,
		/** @brief COM7: under Windows, /dev/ttyS6 under Linux */
		P6 = 6,
		/** @brief COM8: under Windows, /dev/ttyS7 under Linux */
		P7 = 7
	};

	/** @brief Baud rate constants. */
	enum Baud
	{
		B50 = 50,
		B75 = 75,
		B110 = 110,
		B134 = 134,
		B150 = 150,
		B200 = 200,
		B300 = 300,
		B600 = 600,
		B1200 = 1200,
		B1800 = 1800,
		B2400 = 2400,
		B4800 = 4800,
		B7200 = 7200,
		B9600 = 9600,
		B14400 = 14400,
		B19200 = 19200,
		B38400 = 38400,
		B57600 = 57600,
		B115200 = 115200,
		B128000 = 128000
	};
	
	/** @brief Data bits constants. */
	enum DataBits
	{
		FOUR = 4,
		FIVE = 5,
		SIX = 6,
		SEVEN = 7,
		EIGHT = 8
	};
	
	/** @brief Parity type constants. */
	enum Parity
	{
		NONE = 0,
		ODD = 1,
		EVEN = 2
	};
	
	/** @brief Stop bit constants */
	enum StopBits
	{
		/** @brief 1 stop bit. */
		ONE = 1, 
		/** @brief 1.5 stop bits. */
		ONEFIVE = 15,
		/** @brief 2 stop bits. */
		TWO = 2
	};

public:
	/** @brief Stores the serial port address for this configuration. */
	Port port;
	/** @brief Stores the baud rate for this serial configuaration. */
	Baud baud;
	/** @brief Stores the data bits for this serial configuration.  */
	DataBits dataBits;
	/** @brief Stores the parity type for this serial configuration. */
	Parity parity;
	/** @brief Stores the stop bit configuration.  */
	StopBits stopBits;

public:
	SerialConfiguration(
		Port port = P0,
		Baud baud = B57600,
		DataBits dataBits = EIGHT,
		Parity parity = NONE,
		StopBits stopBits = ONE
	);
	virtual ~SerialConfiguration();
};

};

#endif //COMM_SERIALCONFIGURATION_H
