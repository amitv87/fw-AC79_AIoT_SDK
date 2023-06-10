.section .sys.version, "ax"

.global lib_mqtt_version

lib_mqtt_version:

#ifdef CONFIG_RELEASE_ENABLE

#else

.asciz "MQTT-*modified*--@20230515-$de4db24"
#endif
