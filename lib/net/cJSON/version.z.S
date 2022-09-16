.section .sys.version, "ax"

.global lib_cjson_version

lib_cjson_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "CJSON-*modified*--@20220916-$d1adac0"
#endif
