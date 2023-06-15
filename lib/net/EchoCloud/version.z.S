.section .sys.version, "ax"

.global lib_echocloud_version

lib_echocloud_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "ECHOCLOUD-*modified*--@20230614-$4ee734f"
#endif
