#include "system/includes.h"
#include "wifi/wifi_connect.h"
#include "lwip.h"
#include "dhcp_srv/dhcp_srv.h"
#include "event/net_event.h"
#include "net/assign_macaddr.h"
#include "syscfg_id.h"
#include "lwip/sockets.h"

char chl_tx_en_detpwr(char en);
#define INTERVAL_MS 10
static u16 g_det_timer = 0;

static void det_pwr_status(void *p)
{
    char detpwr = chl_tx_en_detpwr(1);
    /* printf("detpwr:%d\n", detpwr); */
}

void wifi_adaptivity_timer_del(void)
{
    if (g_det_timer) {
        sys_timer_del(g_det_timer);
        g_det_timer = 0;
    }
}

static void wifi_adaptivity_task(void *priv)
{
    enum wifi_sta_connect_state state;
    while (1) {
        printf("Connecting to the network...\n");
        state = wifi_get_sta_connect_state();
        if (WIFI_STA_NETWORK_STACK_DHCP_SUCC == state) {
            printf("Network connection is successful!\n");
            break;
        }
        os_time_dly(100);
    }

    if (!g_det_timer) {
        g_det_timer = sys_timer_add_to_task("app_core", NULL, det_pwr_status, INTERVAL_MS);
    }
}

void wifi_adaptivity_start(void)
{
    if (thread_fork("wifi_adaptivity_task", 10, 256, 0, NULL, wifi_adaptivity_task, NULL) != OS_NO_ERR) {
        printf("thread fork fail\n");
    }
}
