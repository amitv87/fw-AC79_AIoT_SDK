.section .sys.version, "ax"

.global lib_wolfssl_version

lib_wolfssl_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "WOLFSSL-*modified*--@20230515-$de4db24"
#endif
