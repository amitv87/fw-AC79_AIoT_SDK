.section .sys.version, "ax"

.global lib_mqtt_version

lib_mqtt_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "MQTT-*modified*--@20220916-$d1adac0"
#endif
