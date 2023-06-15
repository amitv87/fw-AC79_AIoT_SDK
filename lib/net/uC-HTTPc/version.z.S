.section .sys.version, "ax"

.global lib_uc_httpc_version

lib_uc_httpc_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "UC_HTTPC-*modified*--@20230614-$4ee734f"
#endif
