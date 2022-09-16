.section .sys.version, "ax"

.global lib_zliblite_version

lib_zliblite_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "ZLIBLITE-*modified*--@20220916-$d1adac0"
#endif
