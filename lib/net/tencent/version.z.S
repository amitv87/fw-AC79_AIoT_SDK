.section .sys.version, "ax"

.global lib_tencent_version

lib_tencent_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "TENCENT-*modified*--@20220916-$d1adac0"
#endif
