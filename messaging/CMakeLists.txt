SET(messaging_path "${CMAKE_SOURCE_DIR}/../../messaging/coap/")

SET(messaging_srcs
	${messaging_path}/coap.c
	${messaging_path}/engine.c
	${messaging_path}/observe.c
	${messaging_path}/separate.c
	${messaging_path}/transactions.c)

ADD_LIBRARY(objmessaging_client OBJECT ${messaging_srcs})
TARGET_COMPILE_DEFINITIONS(objmessaging_client PUBLIC
	"-DOC_CLIENT")

ADD_LIBRARY(objmessaging_server OBJECT ${messaging_srcs})
TARGET_COMPILE_DEFINITIONS(objmessaging_server PUBLIC
	"-DOC_SERVER")

ADD_LIBRARY(objmessaging_client_server OBJECT ${messaging_srcs})
TARGET_COMPILE_DEFINITIONS(objmessaging_client_server PUBLIC
	"-DOC_CLIENT"
	"-DOC_SERVER")
