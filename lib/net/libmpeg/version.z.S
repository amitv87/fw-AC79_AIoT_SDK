.section .sys.version, "ax"

.global lib_mpeg_version

lib_mpeg_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "MPEG-*modified*--@20220916-$d1adac0"
#endif
