.section .sys.version, "ax"

.global lib_device_vad_version

lib_device_vad_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "LIBVAD-*modified*--@20230515-$de4db24"
#endif
