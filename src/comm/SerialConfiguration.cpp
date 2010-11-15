#include "SerialConfiguration.h"

namespace comm
{

/**
 * @brief Creates and initializes a SerialConfiguration object.
 * @param port Serial Port address constant.
 * @param baud Desired baud rate.
 * @param dataBits Desired data bits.
 * @param parity Desired parity checking.
 * @param stopBits Desired number of stop bits.
 */
SerialConfiguration::SerialConfiguration(Port port, Baud baud, DataBits dataBits, Parity parity, StopBits stopBits)
{
	this->port = port;
	this->baud = baud;
	this->dataBits = dataBits;
	this->parity = parity;
	this->stopBits = stopBits;
}

/**
 * @brief Does nothing.
 */
SerialConfiguration::~SerialConfiguration()
{
}

};
