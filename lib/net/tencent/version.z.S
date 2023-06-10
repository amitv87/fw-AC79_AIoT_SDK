.section .sys.version, "ax"

.global lib_tencent_version

lib_tencent_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "TENCENT-*modified*--@20230515-$de4db24"
#endif
