
.section .sys.version, "ax"

.global lib_nopoll_version

lib_nopoll_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "LIBNOPOLL-*modified*--@20230515-$de4db24"
#endif
