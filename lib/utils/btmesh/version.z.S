.section .sys.version, "ax"

.global lib_btmesh_version

lib_btmesh_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "BTMESH-*modified*--@20231104-$2791ac1"
#endif

