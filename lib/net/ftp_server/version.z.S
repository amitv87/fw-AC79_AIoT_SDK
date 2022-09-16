.section .sys.version, "ax"

.global lib_ftpserver_version

lib_ftpserver_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "FTPSERVER-*modified*--@20220916-$d1adac0"
#endif
