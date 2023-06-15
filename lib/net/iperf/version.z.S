.section .sys.version, "ax"

.global lib_iperf_version

lib_iperf_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "IPERF-*modified*--@20230614-$4ee734f"
#endif
