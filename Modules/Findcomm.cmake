# Use this Find script as a template to find the comm library
# Use
# COMM_INCLUDE_DIR
# COMM_LIBRARIES

FIND_PATH(COMM_INCLUDE_DIR comm/Connection.h
	${CMAKE_INCLUDE_PATH}
	$ENV{COMMDIR}/include
	/usr/local/comm/include
	/usr/local/include
	/usr/include
	$ENV{ProgramFiles}/comm/include
	C:/comm/include
)

IF (NOT COMM_INCLUDE_DIR_FOUND)
	IF (COMM_INCLUDE_DIR)
		MESSAGE(STATUS "Looking for comm headers -- found " ${COMM_INCLUDE_DIR}/comm/Connection.h)
		SET(COMM_INCLUDE_DIR_FOUND 1 CACHE INTERNAL "comm headers found")
	ELSE (COMM_INCLUDE_DIR)
		MESSAGE(FATAL_ERROR 
			"-- Looking for comm headers -- not found\n"
			"Please install the comm library or adjust CMAKE_INCLUDE_PATH\n"
			"e.g. cmake -DCMAKE_INCLUDE_PATH=/path-to-comm/include ..."
		)
	ENDIF (COMM_INCLUDE_DIR)
ENDIF (NOT COMM_INCLUDE_DIR_FOUND)

FIND_LIBRARY(COMM_LIBRARY
	NAMES comm
	PATHS
	${CMAKE_LIBRARY_PATH}
	$ENV{COMMDIR}/lib
	/usr/local/comm/lib
	/usr/local/lib
	/usr/lib
	$ENV{ProgramFiles}/comm/lib
	C:/comm/lib
)

IF(WIN32)
	# For Win32 add the ws2_32 library which implements the sockets on Win32 Platforms
	SET(COMM_LIBRARIES ${COMM_LIBRARY} ws2_32)
ELSE(WIN32)
	SET(COMM_LIBRARIES ${COMM_LIBRARY})
ENDIF(WIN32)

IF (NOT COMM_LIBRARY_FOUND)
	IF (COMM_LIBRARY)
		MESSAGE(STATUS "Looking for comm library -- found " ${COMM_LIBRARY})
		SET(COMM_LIBRARY_FOUND 1 CACHE INTERNAL "comm library found")
	ELSE (COMM_LIBRARY)
		MESSAGE(FATAL_ERROR 
			"-- Looking for comm library -- not found\n"
			"Please install the comm library or adjust CMAKE_LIBRARY_PATH\n"
			"e.g. cmake -DCMAKE_LIBRARY_PATH=/path-to-comm/lib ..."
		)
	ENDIF (COMM_LIBRARY)
ENDIF (NOT COMM_LIBRARY_FOUND)

MARK_AS_ADVANCED(
	COMM_INCLUDE_DIR
	COMM_LIBRARY
	COMM_LIBRARIES
) 
