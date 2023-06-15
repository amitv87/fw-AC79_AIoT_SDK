.section .sys.version, "ax"

.global lib_mqtt_version

lib_mqtt_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "MQTT-*modified*--@20230614-$4ee734f"
#endif
