.section .sys.version, "ax"

.global lib_mongoose_version

lib_mongoose_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "MONGOOSE-*modified*--@20220916-$d1adac0"
#endif
