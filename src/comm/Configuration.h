#ifndef COMM_CONFIGURATION_H
#define COMM_CONFIGURATION_H

namespace comm
{

/**
 * @class Configuration Configuration.h comm/Configuration.h
 * @brief Base class for communication configurations.
 * @author Martin Wojtczyk <wojtczyk@in.tum.de>
 * 
 * Configuration is the base class for different kinds of communication
 * configurations to keep the settings for a serial port for example.
 */	
class Configuration
{
public:
	Configuration();
	virtual ~Configuration();
};

};

#endif //COMM_CONFIGURATION_H
