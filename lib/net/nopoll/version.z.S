
.section .sys.version, "ax"

.global lib_nopoll_version

lib_nopoll_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "LIBNOPOLL-*modified*--@20230614-$4ee734f"
#endif
