CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(iotivity-constrained)

INCLUDE(GNUInstallDirs)
INCLUDE(FindPkgConfig)

INCLUDE(../../deps/CMakeLists.txt)
INCLUDE(../../util/CMakeLists.txt)
INCLUDE(../../api/CMakeLists.txt)
INCLUDE(../../messaging/CMakeLists.txt)
INCLUDE(../../security/CMakeLists.txt)

# Global C flags
SET(CMAKE_C_FLAGS "${CMAKE_CLFLAGS} -g -fPIC -fno-asynchronous-unwind-tables -fno-omit-frame-pointer -ffreestanding -Os -fno-stack-protector -ffunction-sections -fdata-sections -fno-reorder-functions -fno-defer-pop -fno-strict-overflow -std=gnu99 -Wall -Wextra -Werror -pedantic")
SET(extra_cflags "")

# Global include directories
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/../../
	${CMAKE_SOURCE_DIR}/../../include)

# library version
SET(VERSION_MAJOR 1)
SET(VERSION_MINOR 0)
SET(VERSION_PATCH 0)
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Build options
IF(DEBUG)
	SET(extra_cflags "${extra_cflags} -DOC_DEBUG")
ENDIF()

IF(DYNAMIC)
	SET(extra_cflags "${extra_cflags} -DOC_DYNAMIC_ALLOCATION")
ENDIF()

IF(IPV4)
	SET(extra_cflags "${extra_cflags} -DOC_IPV4")
ENDIF()

IF(TCP)
	SET(extra_cflags "${extra_cflags} -DOC_TCP")
ENDIF()

IF(NOT (SECURE EQUAL 0))
	SET(extra_cflags "${extra_cflags} -DOC_SECURITY")
ENDIF()

ADD_DEFINITIONS(${extra_cflags})

# Porting layers
SET(port_srcs
	abort.c
	clock.c
	ipadapter.c
	random.c
	storage.c
	tcpadapter.c)

ADD_LIBRARY(objport_client OBJECT ${port_srcs})
TARGET_COMPILE_DEFINITIONS(objport_client PUBLIC
	"-DOC_CLIENT")

ADD_LIBRARY(objport_server OBJECT ${port_srcs})
TARGET_COMPILE_DEFINITIONS(objport_server PUBLIC
	"-DOC_SERVER")

ADD_LIBRARY(objport_client_server OBJECT ${port_srcs})
TARGET_COMPILE_DEFINITIONS(objport_client_server PUBLIC
	"-DOC_CLIENT"
	"-DOC_SERVER")

# libraries
# - client role (shared and static)
# - server role (shared and static)
# - client-server role (shared and static)
SET(objs_client
	$<TARGET_OBJECTS:objapi_client>
	$<TARGET_OBJECTS:objmessaging_client>
	$<TARGET_OBJECTS:objport_client>
	$<TARGET_OBJECTS:objutil>
	$<TARGET_OBJECTS:objcbor>)

SET(objs_server
	$<TARGET_OBJECTS:objapi_server>
	$<TARGET_OBJECTS:objmessaging_server>
	$<TARGET_OBJECTS:objport_server>
	$<TARGET_OBJECTS:objutil>
	$<TARGET_OBJECTS:objcbor>)

SET(objs_client_server
	$<TARGET_OBJECTS:objapi_client_server>
	$<TARGET_OBJECTS:objmessaging_client_server>
	$<TARGET_OBJECTS:objport_client_server>
	$<TARGET_OBJECTS:objutil>
	$<TARGET_OBJECTS:objcbor>)

IF(NOT (SECURE EQUAL 0))
	SET(objs_client
		${objs_client}
		$<TARGET_OBJECTS:objsecurity_client>
		$<TARGET_OBJECTS:objdtls>)
	SET(objs_server
		${objs_server}
		$<TARGET_OBJECTS:objsecurity_server>
		$<TARGET_OBJECTS:objdtls>)
	SET(objs_client_server
		${objs_client_server}
		$<TARGET_OBJECTS:objsecurity_client_server>
		$<TARGET_OBJECTS:objdtls>)
ENDIF()

ADD_LIBRARY(libclient SHARED ${objs_client})
SET_TARGET_PROPERTIES(libclient PROPERTIES
	VERSION ${VERSION}
	SOVERSION ${VERSION_MAJOR}
	OUTPUT_NAME ${PROJECT_NAME}-client)
INSTALL(TARGETS libclient LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

ADD_LIBRARY(libclient_static STATIC ${objs_client})
SET_TARGET_PROPERTIES(libclient_static PROPERTIES
	OUTPUT_NAME ${PROJECT_NAME}-client)
INSTALL(TARGETS libclient_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

ADD_LIBRARY(libserver SHARED ${objs_server})
SET_TARGET_PROPERTIES(libserver PROPERTIES
	VERSION ${VERSION}
	SOVERSION ${VERSION_MAJOR}
	OUTPUT_NAME ${PROJECT_NAME}-server)
INSTALL(TARGETS libserver LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

ADD_LIBRARY(libserver_static STATIC ${objs_server})
SET_TARGET_PROPERTIES(libserver_static PROPERTIES
	OUTPUT_NAME ${PROJECT_NAME}-server)
INSTALL(TARGETS libserver_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

ADD_LIBRARY(libclient_server SHARED ${objs_client_server})
SET_TARGET_PROPERTIES(libclient_server PROPERTIES
	VERSION ${VERSION}
	SOVERSION ${VERSION_MAJOR}
	OUTPUT_NAME ${PROJECT_NAME}-client-server)
INSTALL(TARGETS libclient_server LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

ADD_LIBRARY(libclient_server_static STATIC ${objs_client_server})
SET_TARGET_PROPERTIES(libclient_server_static PROPERTIES
	OUTPUT_NAME ${PROJECT_NAME}-client-server)
INSTALL(TARGETS libclient_server_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Samples
SET(samples_servers
	server_linux
	simpleserver
	server_collections_linux
	server_block_linux
	smart_home_server_linux
	multi_device_server_linux)

SET(samples_clients
	client_linux
	smart_lock_linux
	temp_sensor_client_linux
	simpleclient
	client_collections_linux
	client_block_linux
	multi_device_client_linux)

FOREACH(app ${samples_servers})
	ADD_EXECUTABLE(${app} ${CMAKE_SOURCE_DIR}/../../apps/${app}.c)
	TARGET_LINK_LIBRARIES(${app} libserver "-lm -pthread -lrt")
	TARGET_COMPILE_DEFINITIONS(${app} PUBLIC "-DOC_SERVER")
	INSTALL(TARGETS ${app} DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/)
ENDFOREACH()

FOREACH(app ${samples_clients})
	ADD_EXECUTABLE(${app} ${CMAKE_SOURCE_DIR}/../../apps/${app}.c)
	TARGET_LINK_LIBRARIES(${app} libclient "-lm -pthread -lrt")
	TARGET_COMPILE_DEFINITIONS(${app} PUBLIC "-DOC_CLIENT")
	INSTALL(TARGETS ${app} DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/)
ENDFOREACH()

# onboarding tool
IF((NOT (SECURE EQUAL 0)) AND DYNAMIC)
	ADD_EXECUTABLE(onboarding_tool ${CMAKE_SOURCE_DIR}/../../onboarding_tool/obtmain.c)
	TARGET_LINK_LIBRARIES(onboarding_tool libclient "-lm -pthread -lrt")
	TARGET_COMPILE_DEFINITIONS(onboarding_tool PUBLIC "-DOC_CLIENT")
	INSTALL(TARGETS onboarding_tool DESTINATION ${CMAKE_INSTALL_LIBDIR}/iotivity-constrained/)
ENDIF()

# pc files
SET(prefix ${CMAKE_INSTALL_PREFIX})
SET(exec_prefix "${prefix}/${CMAKE_INSTALL_BINDIR}")
SET(libdir "${prefix}/${CMAKE_INSTALL_LIBDIR}")
SET(includedir "${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")
SET(version ${VERSION})

CONFIGURE_FILE(${PROJECT_NAME}-client.pc.in ${PROJECT_NAME}-client.pc @ONLY)
CONFIGURE_FILE(${PROJECT_NAME}-server.pc.in ${PROJECT_NAME}-server.pc @ONLY)
CONFIGURE_FILE(${PROJECT_NAME}-client-server.pc.in ${PROJECT_NAME}-client-server.pc @ONLY)

INSTALL(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-client.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
INSTALL(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-server.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
INSTALL(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-client-server.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# header files
FILE(GLOB main_headers "${CMAKE_SOURCE_DIR}/../../include/*.h"
	${CMAKE_SOURCE_DIR}/../../port/linux/config.h)
INSTALL(FILES ${main_headers}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/)

FILE(GLOB port_headers "${CMAKE_SOURCE_DIR}/../../port/*.h")
INSTALL(FILES ${port_headers}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/port/)

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/../../util
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
	FILES_MATCHING PATTERN "*.h")

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/../../deps/tinycbor/src
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/deps/tinycbor/
	FILES_MATCHING PATTERN "*.h")

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/../../messaging/coap
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/messaging/
	FILES_MATCHING PATTERN "*.h")

