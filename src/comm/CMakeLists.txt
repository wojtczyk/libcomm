PROJECT(COMM)

IF (CMAKE_BUILD_TYPE)
	STRING(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
	STRING(COMPARE EQUAL ${BUILD_TYPE} "debug" DEBUG)
	STRING(COMPARE EQUAL ${BUILD_TYPE} "relwithdebinfo" RELWITHDEBINFO)
	IF (DEBUG OR RELWITHDEBINFO)
		ADD_DEFINITIONS(-DDEBUG)
	ENDIF (DEBUG OR RELWITHDEBINFO)
ENDIF (CMAKE_BUILD_TYPE)

SET(HDRS
	Configuration.h
	Connection.h
	SerialConfiguration.h
	SerialPort.h
	SerialPortWin32.h
	SocketConfiguration.h
	Socket.h
	UdpSocket.h
	UdpSocketWin32.h
	UdpSocketPosix.h
	TcpSocket.h
	TcpSocketWin32.h
	TcpSocketPosix.h
)

SET(SRCS
	Configuration.cpp
	Connection.cpp
	SerialConfiguration.cpp
	SerialPort.cpp
	SerialPortWin32.cpp
	SocketConfiguration.cpp
	Socket.cpp
	UdpSocket.cpp
	UdpSocketWin32.cpp
	UdpSocketPosix.cpp
	TcpSocket.cpp
	TcpSocketWin32.cpp
	TcpSocketPosix.cpp
)	

IF (WIN32)
	ADD_LIBRARY(comm STATIC ${HDRS} ${SRCS})
	TARGET_LINK_LIBRARIES(comm)
ELSE (WIN32)
	ADD_LIBRARY(comm SHARED ${HDRS} ${SRCS})
	# assume a Posix compatible system, TODO: refined platform check
	ADD_DEFINITIONS(-DPOSIX)
ENDIF (WIN32)
SET_TARGET_PROPERTIES(comm PROPERTIES VERSION ${VERSION})

INSTALL_TARGETS(/lib comm)
INSTALL_FILES(/include/comm FILES Configuration.h)
INSTALL_FILES(/include/comm FILES Connection.h)
INSTALL_FILES(/include/comm FILES SerialConfiguration.h)
INSTALL_FILES(/include/comm FILES SerialPort.h)
INSTALL_FILES(/include/comm FILES SerialPortWin32.h)
INSTALL_FILES(/include/comm FILES SocketConfiguration.h)
INSTALL_FILES(/include/comm FILES Socket.h)
INSTALL_FILES(/include/comm FILES UdpSocket.h)
INSTALL_FILES(/include/comm FILES UdpSocketWin32.h)
INSTALL_FILES(/include/comm FILES UdpSocketPosix.h)
INSTALL_FILES(/include/comm FILES TcpSocket.h)
INSTALL_FILES(/include/comm FILES TcpSocketWin32.h)
INSTALL_FILES(/include/comm FILES TcpSocketPosix.h)
