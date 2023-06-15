.section .sys.version, "ax"

.global lib_cjson_version

lib_cjson_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "CJSON-*modified*--@20230614-$4ee734f"
#endif
