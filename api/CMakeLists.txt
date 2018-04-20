SET(api_path "${CMAKE_SOURCE_DIR}/../../api/")

SET(api_srcs
	${api_path}/oc_base64.c
	${api_path}/oc_blockwise.c
	${api_path}/oc_buffer.c
	${api_path}/oc_client_api.c
	${api_path}/oc_collection.c
	${api_path}/oc_core_res.c
	${api_path}/oc_discovery.c
	${api_path}/oc_endpoint.c
	${api_path}/oc_helpers.c
	${api_path}/oc_introspection.c
	${api_path}/oc_main.c
	${api_path}/oc_network_events.c
	${api_path}/oc_rep.c
	${api_path}/oc_ri.c
	${api_path}/oc_server_api.c
	${api_path}/oc_uuid.c)

ADD_LIBRARY(objapi_client OBJECT ${api_srcs})
TARGET_COMPILE_DEFINITIONS(objapi_client PUBLIC
	"-DOC_CLIENT")

ADD_LIBRARY(objapi_server OBJECT ${api_srcs})
TARGET_COMPILE_DEFINITIONS(objapi_server PUBLIC
	"-DOC_SERVER")

ADD_LIBRARY(objapi_client_server OBJECT ${api_srcs})
TARGET_COMPILE_DEFINITIONS(objapi_client_server PUBLIC
	"-DOC_CLIENT"
	"-DOC_SERVER")
