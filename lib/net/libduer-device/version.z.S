.section .sys.version, "ax"

.global lib_duer_version

lib_duer_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "DUER-*modified*--@20231129-$1a448c5"
#endif
