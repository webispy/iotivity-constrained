SET(util_path "${CMAKE_SOURCE_DIR}/../../util/")

ADD_LIBRARY(objutil OBJECT
	${util_path}/oc_etimer.c
	${util_path}/oc_list.c
	${util_path}/oc_memb.c
	${util_path}/oc_mmem.c
	${util_path}/oc_process.c
	${util_path}/oc_timer.c)

TARGET_INCLUDE_DIRECTORIES(objutil PUBLIC
	${util_path}/)
