SET(deps_path "${CMAKE_SOURCE_DIR}/../../deps/")

IF(SECURE)
	SET(dtls_srcs
		${deps_path}/mbedtls/library/aes.c
		${deps_path}/mbedtls/library/aesni.c
		${deps_path}/mbedtls/library/arc4.c
		${deps_path}/mbedtls/library/asn1parse.c
		${deps_path}/mbedtls/library/asn1write.c
		${deps_path}/mbedtls/library/base64.c
		${deps_path}/mbedtls/library/bignum.c
		${deps_path}/mbedtls/library/blowfish.c
		${deps_path}/mbedtls/library/camellia.c
		${deps_path}/mbedtls/library/ccm.c
		${deps_path}/mbedtls/library/cipher.c
		${deps_path}/mbedtls/library/cipher_wrap.c
		${deps_path}/mbedtls/library/cmac.c
		${deps_path}/mbedtls/library/ctr_drbg.c
		${deps_path}/mbedtls/library/des.c
		${deps_path}/mbedtls/library/dhm.c
		${deps_path}/mbedtls/library/ecdh.c
		${deps_path}/mbedtls/library/ecdsa.c
		${deps_path}/mbedtls/library/ecjpake.c
		${deps_path}/mbedtls/library/ecp.c
		${deps_path}/mbedtls/library/ecp_curves.c
		${deps_path}/mbedtls/library/entropy.c
		${deps_path}/mbedtls/library/entropy_poll.c
		${deps_path}/mbedtls/library/error.c
		${deps_path}/mbedtls/library/gcm.c
		${deps_path}/mbedtls/library/havege.c
		${deps_path}/mbedtls/library/hmac_drbg.c
		${deps_path}/mbedtls/library/md.c
		${deps_path}/mbedtls/library/md2.c
		${deps_path}/mbedtls/library/md4.c
		${deps_path}/mbedtls/library/md5.c
		${deps_path}/mbedtls/library/md_wrap.c
		${deps_path}/mbedtls/library/oid.c
		${deps_path}/mbedtls/library/padlock.c
		${deps_path}/mbedtls/library/pem.c
		${deps_path}/mbedtls/library/pk.c
		${deps_path}/mbedtls/library/pk_wrap.c
		${deps_path}/mbedtls/library/pkcs12.c
		${deps_path}/mbedtls/library/pkcs5.c
		${deps_path}/mbedtls/library/pkparse.c
		${deps_path}/mbedtls/library/pkwrite.c
		${deps_path}/mbedtls/library/platform.c
		${deps_path}/mbedtls/library/ripemd160.c
		${deps_path}/mbedtls/library/rsa.c
		${deps_path}/mbedtls/library/sha1.c
		${deps_path}/mbedtls/library/sha256.c
		${deps_path}/mbedtls/library/sha512.c
		${deps_path}/mbedtls/library/threading.c
		${deps_path}/mbedtls/library/timing.c
		${deps_path}/mbedtls/library/version.c
		${deps_path}/mbedtls/library/version_features.c
		${deps_path}/mbedtls/library/xtea.c
		${deps_path}/mbedtls/library/pkcs11.c
		${deps_path}/mbedtls/library/x509.c
		${deps_path}/mbedtls/library/x509_crt.c
		${deps_path}/mbedtls/library/debug.c
		${deps_path}/mbedtls/library/net_sockets.c
		${deps_path}/mbedtls/library/ssl_cache.c
		${deps_path}/mbedtls/library/ssl_ciphersuites.c
		${deps_path}/mbedtls/library/ssl_cli.c
		${deps_path}/mbedtls/library/ssl_cookie.c
		${deps_path}/mbedtls/library/ssl_srv.c
		${deps_path}/mbedtls/library/ssl_ticket.c
		${deps_path}/mbedtls/library/ssl_tls.c)

	IF(NOT DYNAMIC)
		SET(dtls_srcs ${dtls_srcs}
			${deps_path}/mbedtls/library/memory_buffer_alloc.c)
	ENDIF()

	ADD_LIBRARY(objdtls OBJECT ${dtls_srcs})

	INCLUDE_DIRECTORIES(${deps_path}/mbedtls/include)

	TARGET_COMPILE_DEFINITIONS(objdtls PUBLIC "-D__OC_RANDOM")
ENDIF()

ADD_LIBRARY(objcbor OBJECT
	${deps_path}/tinycbor/src/cborencoder.c
	${deps_path}/tinycbor/src/cborencoder_close_container_checked.c
	${deps_path}/tinycbor/src/cborparser.c)
