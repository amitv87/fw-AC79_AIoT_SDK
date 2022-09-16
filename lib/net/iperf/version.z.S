.section .sys.version, "ax"

.global lib_iperf_version

lib_iperf_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "IPERF-*modified*--@20220916-$d1adac0"
#endif
