.section .sys.version, "ax"

.global lib_http_server_version

lib_http_server_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "HTTP_SERVER-*modified*--@20230614-$4ee734f"
#endif
