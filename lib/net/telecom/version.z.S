.section .sys.version, "ax"

.global lib_telecom_version

lib_telecom_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "TELECOM-*modified*--@20230515-$de4db24"
#endif
