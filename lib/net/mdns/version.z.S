.section .sys.version, "ax"

.global lib_mdns_version

lib_mdns_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "MDNS-*modified*--@20220916-$d1adac0"
#endif
