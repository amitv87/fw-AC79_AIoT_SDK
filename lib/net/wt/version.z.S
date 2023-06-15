.section .sys.version, "ax"

.global lib_wt_version

lib_wt_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "WT-*modified*--@20230614-$4ee734f"
#endif
