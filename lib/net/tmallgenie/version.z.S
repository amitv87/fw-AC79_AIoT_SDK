.section .sys.version, "ax"

.global lib_tmallgenie_version

lib_tmallgenie_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "TMALLGENIE-*modified*--@20220916-$d1adac0"
#endif
