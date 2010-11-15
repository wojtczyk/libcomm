#ifdef WIN32 // Build SerialPortWin32 only if compiled on a Win32 platform

#include "Configuration.h"
#include "SerialConfiguration.h"
#include "SerialPortWin32.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace comm
{

/**
 * @brief Does nothing.
 */
SerialPortWin32::SerialPortWin32()
{
};

/**
 * @brief Does nothing.
 */
SerialPortWin32::~SerialPortWin32()
{
};

/**
 * @brief Creates an instance of the SerialPortWin32 class.
 * @return A pointer to the created object.
 * 
 * The caller should make sure, that the memory of the returned object is freed
 * once it is no longer needed, by calling delete.
 */
SerialPort* SerialPortWin32::create() throw(std::exception)
{
	return new SerialPortWin32();
};

/**
 * @brief Store the configuration for this serial communication object
 * @param configuration The configuration parameters for the serial port.
 * 
 * This method actually only stores the configuration parameters. It does not
 * already configure the serial port itself.
 */
void SerialPortWin32::configure(const SerialConfiguration* configuration) throw(std::exception)
{
	string functionSignature = "void SerialPortWin32::configure(Configuration* configuration)";
	
	// Copy configuration data
	this->serialConfiguration = *configuration;
};

/**
 * @brief Evaluates the configuration object and opens the serial port.
 */
void SerialPortWin32::open() throw(std::exception)
{
	string functionSignature = "void SerialPortWin32::open()";
	// TODO check configuration object
	stringstream portStream;
	portStream << "COM" << ((int) serialConfiguration.port) + 1 << ":";
	string port = portStream.str();
	
	// Open the communcication port
	portHandle = CreateFile(port.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if ((long) portHandle == ERROR_FILE_NOT_FOUND)
	{
		throw std::runtime_error(functionSignature + " Communication port not found.");
	}

	// Configure communication port according to the settings previously given
	DCB dcb;
	// Initialize the DCBlength member. 
	dcb.DCBlength = sizeof(DCB); 
	
	// Get the default port setting information.
	GetCommState(portHandle, &dcb);
	
	// Change the DCB structure settings.
	dcb.BaudRate = serialConfiguration.baud; // Current baud 
	dcb.fBinary = TRUE;               // Binary mode; no EOF check 

	if (serialConfiguration.parity != SerialConfiguration::Parity::NONE)
	{
		dcb.fParity = TRUE;               // Enable parity checking 
	}
	else
	{
		dcb.fParity = FALSE;
	};
	dcb.fOutxCtsFlow = FALSE;         // No CTS output flow control 
	dcb.fOutxDsrFlow = FALSE;         // No DSR output flow control 
	dcb.fDtrControl = DTR_CONTROL_ENABLE; 
	                                      // DTR flow control type 
	dcb.fDsrSensitivity = FALSE;      // DSR sensitivity 
	dcb.fTXContinueOnXoff = TRUE;     // XOFF continues Tx 
	dcb.fOutX = FALSE;                // No XON/XOFF out flow control 
	dcb.fInX = FALSE;                 // No XON/XOFF in flow control 
	dcb.fErrorChar = FALSE;           // Disable error replacement 
	dcb.fNull = FALSE;                // Disable null stripping 
	dcb.fRtsControl = RTS_CONTROL_ENABLE; 
	                                      // RTS flow control 
	dcb.fAbortOnError = FALSE;        // Do not abort reads/writes on error
	dcb.ByteSize = serialConfiguration.dataBits; // Number of bits/byte, 4-8 

	// dcb.Parity = 1;            // 0-4=no,odd,even,mark,space 
	switch (serialConfiguration.parity)
	{
		case SerialConfiguration::Parity::NONE:
			dcb.Parity = 0;
			break;
		
		case SerialConfiguration::Parity::ODD:
			dcb.Parity = 1;
			break;
		
		case SerialConfiguration::Parity::EVEN:
			dcb.Parity = 2;
			break;
		
		default:
			throw std::runtime_error(functionSignature + " Parity Setting not supported");
	}
	
	// dcb.StopBits = ONESTOPBIT;        // 0,1,2 = 1, 1.5, 2 
	switch (serialConfiguration.stopBits)
	{
		case SerialConfiguration::StopBits::ONE:
			dcb.StopBits = ONESTOPBIT;
			break;
		
		case SerialConfiguration::StopBits::ONEFIVE:
			dcb.StopBits = ONE5STOPBITS;
			break;
		
		case SerialConfiguration::StopBits::TWO:
			dcb.StopBits = TWOSTOPBITS;
			break;
			
		default:
			throw std::runtime_error(functionSignature + " Stop Bit Setting not supported");
	}
	
	DWORD dwError;
	
	// Configure the port according to the specifications of the DCB 
	// structure.
	if (SetCommState(portHandle, &dcb) == false)
	{
		// Could not configure the serial port.
		dwError = GetLastError();
		throw std::runtime_error(functionSignature + " Could not configure the serial port.");
	}

	// Setup Timeouts
	// Retrieve the timeout parameters for all read and write operations
	// on the port. 
	COMMTIMEOUTS commTimeouts;
	GetCommTimeouts(portHandle, &commTimeouts);

	// TODO tune properly if needed	
	// Change the COMMTIMEOUTS structure settings.
	commTimeouts.ReadIntervalTimeout = 100;  
	commTimeouts.ReadTotalTimeoutMultiplier = 1;
	commTimeouts.ReadTotalTimeoutConstant = 100;    
//	commTimeouts.ReadTotalTimeoutMultiplier = 10;
//	commTimeouts.ReadTotalTimeoutConstant = 1000;    
	commTimeouts.WriteTotalTimeoutMultiplier = 10;  
	commTimeouts.WriteTotalTimeoutConstant = 1000;    
	
	// Set the timeout parameters for all read and write operations
	// on the port. 
	if (!SetCommTimeouts(portHandle, &commTimeouts))
	{
		dwError = GetLastError();
		throw std::runtime_error(functionSignature + " Could not setup timeouts for the serial port.");
	};
};

/**
 * @brief Closes the serial port.
 */
void SerialPortWin32::close() throw(std::exception)
{
	CloseHandle(portHandle);
};

/**
 * @brief Sends a string to the serial port.
 * @param sendbuf The send buffer.
 */
int SerialPortWin32::send(const std::string& sendbuf) throw(std::exception)
{
	string functionSignature = "int SerialPortWin32::send(const std::string& sendbuf)";
	
	unsigned int i;
	for (i = 0; i < sendbuf.length(); i++)
	{
		DWORD dwError;
		DWORD dwNumBytesWritten;
		char sendByte = sendbuf[i];

		// send byte by byte as in Windows Plattform SDK
		if (WriteFile(portHandle, &sendByte, 1, &dwNumBytesWritten, NULL) == false)
		{
			dwError = GetLastError();
			throw std::runtime_error(functionSignature + " Error while writing to communication port.");
		};
	};
	
	return i; // return the number of sent bytes
};

/**
 * @brief Read data from the serial port.
 * @return A string containing the received characters.
 * 
 * This method reads as many characters from the serial port as possible. It
 * only stops reading data, after a timeout occurs and returns the read string.
 */
std::string SerialPortWin32::receive() throw(std::exception)
{
	string functionSignature = "std::string SerialPortWin32::receive()";
	DWORD dwError;
	DWORD dwNumBytesTransferred;
	char inbuf;
	DWORD dwCommStatus;
	string returnString = "";

	// Specify a set of events to be monitored for the port.
	SetCommMask(portHandle, EV_RXCHAR);

	// Wait for an event to occur for the port.
	WaitCommEvent(portHandle, &dwCommStatus, 0);
	
	// Re-specify the set of events to be monitored for the port.
	SetCommMask(portHandle, EV_RXCHAR);
	
	if (dwCommStatus & EV_RXCHAR) 
	{
		// Loop for waiting for the data.
		do 
		{
			// Read the data from the serial port.
			if (ReadFile(portHandle, &inbuf, 1, &dwNumBytesTransferred, 0) == false)
			{
				dwError = GetLastError();
				throw std::runtime_error(functionSignature + " Error while reading from communication port.");
			};
			
			if (dwNumBytesTransferred == 1)
			{
				returnString += inbuf;
				// Display the data read.
				cout << "recv(" << (int) inbuf << ")" << endl;
			};
			
		} while (dwNumBytesTransferred == 1);
	};

	return returnString;
};

/**
 * @brief TODO not implemented
 */
int SerialPortWin32::dataAvailable()
{
	return 0;
};

};

#endif // WIN32
