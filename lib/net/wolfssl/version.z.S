.section .sys.version, "ax"

.global lib_wolfssl_version

lib_wolfssl_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "WOLFSSL-*modified*--@20230614-$4ee734f"
#endif
