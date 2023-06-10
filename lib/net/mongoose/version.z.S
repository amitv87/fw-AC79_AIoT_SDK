.section .sys.version, "ax"

.global lib_mongoose_version

lib_mongoose_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "MONGOOSE-*modified*--@20230515-$de4db24"
#endif
