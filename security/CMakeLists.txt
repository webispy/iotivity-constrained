SET(security_path "${CMAKE_SOURCE_DIR}/../../security/")

SET(security_srcs
	${security_path}/oc_acl.c
	${security_path}/oc_cred.c
	${security_path}/oc_doxm.c
	${security_path}/oc_pstat.c
	${security_path}/oc_tls.c
	${security_path}/oc_svr.c
	${security_path}/oc_store.c
	${security_path}/oc_pki.c
	${security_path}/oc_certs.c
	${security_path}/oc_sp.c)

SET(security_client_srcs ${security_srcs})

IF(DYNAMIC)
	SET(security_client_srcs ${security_client_srcs}
		${security_path}/oc_obt.c)
ENDIF()

ADD_LIBRARY(objsecurity_client OBJECT ${security_client_srcs})
TARGET_INCLUDE_DIRECTORIES(objsecurity_client PUBLIC
	${deps_path}/mbedtls/include)
TARGET_COMPILE_DEFINITIONS(objsecurity_client PUBLIC
	"-DOC_CLIENT")

ADD_LIBRARY(objsecurity_server OBJECT ${security_srcs})
TARGET_INCLUDE_DIRECTORIES(objsecurity_server PUBLIC
	${deps_path}/mbedtls/include)
TARGET_COMPILE_DEFINITIONS(objsecurity_server PUBLIC
	"-DOC_SERVER")

ADD_LIBRARY(objsecurity_client_server OBJECT ${security_client_srcs})
TARGET_INCLUDE_DIRECTORIES(objsecurity_client_server PUBLIC
	${deps_path}/mbedtls/include)
TARGET_COMPILE_DEFINITIONS(objsecurity_client_server PUBLIC
	"-DOC_CLIENT"
	"-DOC_SERVER")
