#include "product_main.h"

#ifdef PRODUCT_TEST_ENABLE

#include "sock_api/sock_api.h"
#include "app_config.h"
#include "system/includes.h"
#include "wifi/wifi_connect.h"
#include "lwip.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"


#ifdef PRODUCT_NET_SERVER_ENABLE

#define TXINFO_SIZE			  4
#define USB_DIR_OUT	          0
#define USB_DIR_IN	          0x80
#define WIFI_TXWI_HEAD_SIZE   20
#define WIFI_80211_FILL_SIZE  27 //保留一些字节不填充, 为了避开duration段和上层发送1个字节也支持

static u16 time_hdl = 0;
static u8 breathe_idx = 0;
static int camera_pid = 0;
struct sockaddr_in remote_addr = {0};
static struct sockaddr_in host_dest = {0};
static conn_flag = FALSE, wifi_conn = FALSE;
static u8 conn_ssid[33] = {0}, conn_pwd[64] = {0};
static void *host_sock = NULL, *breathe_sock = NULL;
static OS_SEM asem, bsem, bs_sem, br_sem, camera_sem;


static  const  struct  {
    const char *string;
    u8 phy;
    u8 mcs;
} tx_rate_tab[] = {
    {"1M",		0,		0},
    {"2M",		0,		1},
    {"5.5M",	0,		2},
    {"11M",		0,		3},

    {"6M",		1,		0},
    {"9M",		1,		1},
    {"12M",		1,		2},
    {"18M",		1,		3},
    {"24M",		1,		4},
    {"36M",		1,		5},
    {"48M",		1,		6},
    {"54M",		1,		7},

    {"HTMCS0",	2,		0},
    {"HTMCS1",	2,		1},
    {"HTMCS2",	2,		2},
    {"HTMCS3",	2,		3},
    {"HTMCS4",	2,		4},
    {"HTMCS5",	2,		5},
    {"HTMCS6",	2,		6},
    {"HTMCS7",	2,		7},
};


__attribute__((aligned(4))) static u8 wifi_send_pkg[1564] = {
    0xc6, 0x00, 0x00, 0x04, 0xB0, 0x00, 0x04, 0x80, 0x35, 0x01, 0xB6, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x88, 0x88, /*dst*/ 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6,/*src*/0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,/*BSSID*/ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /*Seq,Frag num*/0x88, 0x88,
};


static u8 breathe_ctl(u8 on);
static void delete_dev_conn(void);
static void build_data_conn(void);


static void wifi_tx_data(u8 *pkg, int len, u32 rate, u8 bw, u8 short_gi)// 最大包1513
{
    u16 *PktLen = &wifi_send_pkg[0];
    u16 *MPDUtotalByteCount = &wifi_send_pkg[10];
    *PktLen = WIFI_80211_FILL_SIZE + len + WIFI_TXWI_HEAD_SIZE + 4 - 8;
    *MPDUtotalByteCount = WIFI_80211_FILL_SIZE + len;

    if (pkg) {
        //put_buf(pkg, len);
        memcpy(&wifi_send_pkg[WIFI_TXWI_HEAD_SIZE + WIFI_80211_FILL_SIZE], pkg, len);
    } else {
        memset(&wifi_send_pkg[WIFI_TXWI_HEAD_SIZE + WIFI_80211_FILL_SIZE], 0xaa, len);
    }

    struct urb urb;
    urb.pipe = USB_DIR_OUT;
    urb.complete = NULL;
    urb.transfer_buffer = wifi_send_pkg;
    urb.transfer_buffer_length = len + WIFI_TXWI_HEAD_SIZE + WIFI_80211_FILL_SIZE + 4;

    PTXWI_STRUC pTxWI = TXINFO_SIZE + (u8 *)urb.transfer_buffer;
    pTxWI->PHYMODE    = tx_rate_tab[rate].phy;
    pTxWI->MCS        = tx_rate_tab[rate].mcs;
    pTxWI->BW         = bw;
    pTxWI->ShortGI    = !short_gi;
    usb_submit_urb(&urb, 0);
}


static void broadcast_task(void *priv)
{
    u8 idx = 0;
    struct wifi_store_info *info = get_cur_wifi_info();
    u8 ch[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    struct product_conn conn = {
        .str = "product_ask",
        .reset = 1,
    };

    conn.mode = info->mode;
    if (info->mode == AP_MODE) {
        strcpy(conn.ssid, info->ssid[info->mode - STA_MODE]);
        strcpy(conn.pwd, info->pwd[info->mode - STA_MODE]);
    }

    for (;;) {
        putchar('C');
        wifi_set_channel(ch[(++idx) % ARRAY_SIZE(ch)]);
        for (u8 i = 0; i < 5; i++) {
            wifi_tx_data(&conn, sizeof(struct product_conn), 0, 0, 0);
            if (!os_sem_accept(&asem)) {
                os_sem_post(&bsem);
                return;
            }
        }
    }
}


static u8 broadcast_ctl(u8 ctl)
{
    static int pid = 0;
    if (ctl & !pid) {
        conn_flag = FALSE;
        thread_fork("broadcast_task", 30, 256, 0, &pid, broadcast_task, NULL);
        return TRUE;
    }

    if (!ctl && pid) {
        os_sem_post(&asem);
        pid = 0;
        //os_sem_pend(&bsem, 0);
        return TRUE;
    }

    return FALSE;
}


static void breathe_timeout_hdl(void *priv)
{
    breathe_idx ++;
    product_info("%s, breathe_idx = %d\n", __FUNCTION__, breathe_idx);
    if (breathe_idx < 3) {
        time_hdl = sys_timeout_add(NULL, breathe_timeout_hdl, BREATHE_TIMEOUT);
    } else {
        breathe_idx = 0;
        breathe_ctl(FALSE);
        delete_camera_data_conn();
        delete_dev_conn();
    }
}


static void breathe_recv_task(void)
{
    u8 recv_buf[32], recv_len, idx = 0;
    socklen_t len = sizeof(struct sockaddr_in);

    for (;;) {
        if (breathe_sock) {
            recv_len = sock_recvfrom(breathe_sock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&remote_addr, &len);
            //product_info("\n recv_len is %d, %s\n", recv_len, recv_buf);
            if (recv_len > 0 && !strcmp(BREATHE_STR, recv_buf)) {
                breathe_idx = 0;
                sys_timer_modify(time_hdl, BREATHE_TIMEOUT);
                if (!host_sock) {
                    product_info("Received data from (ip : %s, port : %d)\r\n", inet_ntoa(remote_addr.sin_addr), remote_addr.sin_port);
                    build_data_conn();
                }
            }
        }

        if (!os_sem_accept(&br_sem)) {
            os_sem_del(&br_sem, 0);
            return;
        }
    }
}


static void breathe_send_task(void *priv)
{
    struct sockaddr_in dest;

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("255.255.255.255");
    dest.sin_port = htons(BREATHE_PORT);

    time_hdl = sys_timeout_add(NULL, breathe_timeout_hdl, BREATHE_TIMEOUT);
    for (;;) {
        if (breathe_sock) {
            sock_sendto(breathe_sock, BREATHE_STR, strlen(BREATHE_STR), 0, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
        }
        os_time_dly(20);

        if (!os_sem_accept(&bs_sem)) {
            os_sem_del(&bs_sem, 0);
            return;
        }
    }
}


static u8 breathe_ctl(u8 on)
{
    u32 opt = 1;

    if (on) {
        if (breathe_sock) {
            return TRUE;
        }

        breathe_sock = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
        if (breathe_sock == NULL) {
            product_err("udp sock_reg fail.\n");
            return FALSE;
        }
        sock_setsockopt(breathe_sock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

        os_sem_create(&bs_sem, 0);
        os_sem_create(&br_sem, 0);
        thread_fork("breathe_send_task", 29, 256, 0, NULL, breathe_send_task, NULL);
        thread_fork("breathe_recv_task", 30, 256, 0, NULL, breathe_recv_task, NULL);
        return TRUE;
    } else {
        if (breathe_sock) {
            sys_timer_del(time_hdl);
            os_sem_post(&bs_sem);
            os_sem_post(&br_sem);
            sock_unreg(breathe_sock);
            breathe_sock = NULL;
            time_hdl = 0;
            return TRUE;
        }
    }

    return FALSE;
}


static void dev_conn_task(void *priv)
{
    wifi_set_connect_sta_block(0);
    wifi_enter_sta_mode(conn_ssid, conn_pwd);
}


static void build_dev_conn(void)
{
    thread_fork("dev_conn_task", 10, 1024, 0, NULL, dev_conn_task, NULL);
}


static void delete_dev_conn(void)
{
    wifi_enter_sta_mode("jijij", "jlkhk");
}


static void host_data_handle_task(void *priv)
{
    s32 len;
    u16 *crc_value;
    u8 rscorr, *data, *read_addr, *l_data, l_idx, *recv_buf, *msg, *str, rscorr_str[4] = {0};
    u32 crc_len, recv_size, total_size, l_len;
    struct comm_head *head;
    json_object *new_obj, *rscorr_obj;

    recv_buf = zalloc(RECV_BUFFER_SIZE);
    head = (struct comm_head *)recv_buf;
    data = recv_buf + sizeof(struct comm_head);

    for (;;) {
        if (!(comm_ops()->online())) {
            os_time_dly(10);
            continue;
        }

        len = host_data_read(recv_buf, MAXP_SIZE_CDC_BULKOUT);
        if (len < sizeof(struct comm_head)) {
            continue;
        }

        if (head->mark[0] != 'J' || head->mark[1] != 'L') {
            continue;
        }

        recv_size  = len;
        read_addr  = recv_buf + len;
        total_size = sizeof(struct comm_head) + head->len + sizeof(u16);
        while (recv_size < total_size) {
            if ((len = host_data_read(read_addr, MAXP_SIZE_CDC_BULKOUT)) <= 0) {
                break;
            }
            recv_size += len;
            read_addr += len;
        }

        if (recv_size < total_size) {
            continue;
        }

        //put_buf(recv_buf, total_size);

        crc_len = sizeof(struct comm_head) + head->len;
        crc_value = (u16 *)(recv_buf + crc_len);
        if (CRC16(head, crc_len) != *crc_value) {
            continue;
        }

        if (!host_sock) {
            msg = zalloc(head->len);
            memcpy(msg, data, head->len);
            new_obj = json_tokener_parse(msg);
            rscorr_obj = json_object_object_get(new_obj, "rscorr");
            sprintf(rscorr_str, "%d", ERR_NET_DISCONNECT);
            json_object_string_set(rscorr_obj, rscorr_str, strlen(rscorr_str));
            str = json_object_get_string(new_obj);
            printf("str = %s\n", str);
            data_respond(0, DATA_TYPE_OPCODE, str, strlen(str));
            json_object_put(new_obj);
        } else {
            sock_sendto(host_sock, recv_buf, total_size, 0, (struct sockaddr *)&host_dest, sizeof(struct sockaddr_in));
        }
    }
}


static void client_data_handle_task(void *priv)
{
    int err, recv_len;
    char recv_buf[1024];

    if (!(host_sock = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL))) {
        product_err("sock_reg fail.\n");
        return;
    }

    host_dest.sin_family = AF_INET;
    host_dest.sin_addr.s_addr = inet_addr(inet_ntoa(remote_addr.sin_addr));
    host_dest.sin_port = htons(HOST_PORT);

    if (sock_connect(host_sock, (struct sockaddr *)&host_dest, sizeof(struct sockaddr_in))) {
        product_err("sock_connect fail.\n");
        sock_unreg(host_sock);
        host_sock = NULL;
        delete_dev_conn();
        return;
    } else {
        product_info("sock_connect succ.\n");
        product_online_tips();
    }

    for (;;) {
        if ((recv_len = sock_recvfrom(host_sock, recv_buf, sizeof(recv_buf), 0, NULL, NULL)) > 0) {
            //put_buf(recv_buf, recv_len);
            host_data_write(recv_buf, recv_len);
        } else {
            product_err("sock_recvfrom err!");
            break;
        }
    }

    if (host_sock) {
        sock_unreg(host_sock);
        host_sock = NULL;
    }
}


static void build_data_conn(void)
{
    if (thread_fork("client_data_handle_task", 20, 1024, 0, NULL, client_data_handle_task, NULL) != OS_NO_ERR) {
        product_err("thread fork fail\n");
    }
}


static void camera_data_handle_task(void *priv)
{
    void *c_sock;
    int recv_len;
    char recv_buf[1024];
    struct sockaddr_in dest = {0};
    struct uvc_video_data {
        int pid;
        u8 *buf;
        u32 len;
        u8 *reqbuf;
        u16 reqlen;
        u16 send_len;
        OS_SEM wait_sem;
        OS_SEM req_sem;
        u8 cur_fmt_id;
        u8 cur_frame_id;
        u8 init;
        u8 end;
        u8 err;
        volatile u8 exit;
        volatile u8 complete;
        spinlock_t lock;
        u32 cur_fps;
        u32 offset;
        u16 width;
        u16 height;
    } *info;
    info = *((u32 *)priv);
    u32(*func)(void *, u8 *, u32) = *(((u32 *)priv) + 1);
    struct net_cmd_type cmd;
    u32 *params = (u32 *)cmd.params;
    char *camera_data = malloc(50 * 1024);
    u32 read_size, recv_size, total_size, remain_size;

    if (!(c_sock = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL))) {
        product_err("sock_reg fail.\n");
        return;
    }

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(inet_ntoa(remote_addr.sin_addr));
    dest.sin_port = htons(CAMERA_PORT);

    if (sock_connect(c_sock, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))) {
        product_err("camera sock_connect fail.\n");
        sock_unreg(c_sock);
        c_sock = NULL;
        return;
    } else {
        product_info("camera_sock_connect succ.\n");
    }

    strcpy(cmd.cmd, NET_CAMERA_OPEN);
    params[0] = info->width;
    params[1] = info->height;
    params[2] = PRODUCT_UVC_FPS;//info->cur_fps;

    if (sock_send(c_sock, &cmd, sizeof(struct net_cmd_type), 0) != sizeof(struct net_cmd_type)) {
        product_err("net camera open err\n");
        return;
    }

    for (;;) {
        if (sock_recvfrom(c_sock, &cmd, sizeof(struct net_cmd_type), 0, NULL, NULL) == sizeof(struct net_cmd_type)) {
            if (strcmp(cmd.cmd, NET_CAMERA_FRAME)) {
                continue;
            }
            recv_size = 0;
            total_size = *((u32 *)cmd.params);
            remain_size = total_size;
            while (remain_size) {
                read_size = remain_size > 1024 ? 1024 : remain_size;
                if ((recv_len = sock_recvfrom(c_sock, camera_data + recv_size, read_size, 0, NULL, NULL)) > 0) {
                    recv_size += recv_len;
                    remain_size = total_size - recv_size;
                } else {
                    break;
                }
            }

            if (!remain_size) {
#if 1
                func(info, camera_data, total_size);
#else
#include "fs/fs.h"
                FILE *fp;
                char *path[32];
                static u32 idx = 0;

                sprintf(path, "storage/sd0/C/myjpg_%d.JPG", idx++);
                if ((fp = fopen(path, "w+"))) {
                    fwrite(camera_data, 1, total_size, fp);
                    fclose(fp);
                }
#endif
            }
        }

        if (!os_sem_accept(&camera_sem)) {
            strcpy(cmd.cmd, NET_CAMERA_CLOSE);
            sock_send(c_sock, &cmd, sizeof(struct net_cmd_type), 0);
            sock_unreg(c_sock);
            c_sock = NULL;
            os_sem_del(&camera_sem, 0);
            free(camera_data);
            camera_pid = 0;
            return;
        }
    }
}


u8 build_camera_data_conn(void *func, void *priv)
{
    static u32 msg[2];
    msg[0] = (u32)priv;
    msg[1] = (u32)func;

    if (camera_pid) {
        return FALSE;
    }

    if (wifi_conn == FALSE) {
        return FALSE;
    }

    os_sem_create(&camera_sem, 0);
    if (thread_fork("camera_data_handle_task", 10, 1024, 0, &camera_pid, camera_data_handle_task, msg) != OS_NO_ERR) {
        product_err("thread fork fail\n");
        return FALSE;
    }
    return TRUE;
}


void delete_camera_data_conn(void)
{
    if (camera_pid) {
        os_sem_post(&camera_sem);
    }
}


static void wifi_rx_frame_cb(void *rxwi, void *header, void *data, u32 len, void *reserve)
{
    u32 size;
    u8 *buf, offset;
    struct product_conn *conn;
    struct wifi_store_info *info = get_cur_wifi_info();

    offset = (info->mode == AP_MODE) ? 27 : 51;
    size = len - offset;
    //if (size < sizeof(struct product_conn)) return;
    buf = ((u8 *)data) + offset;
    conn = buf;

    if (!strcmp(conn->str, "product_resp") && conn_flag == FALSE) {
        conn_flag = TRUE;
        product_info("str = %s, mode = %d, ssid = %s, pwd = %s\n", conn->str, conn->mode, conn->ssid, conn->pwd);
        strcpy(conn_ssid, conn->ssid);
        strcpy(conn_pwd, conn->pwd);
        broadcast_ctl(FALSE);
        build_dev_conn();
    }
}


static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    struct wifi_store_info wifi_default_mode_parm = {0};
    static u8 ssid[33] = "ijjijijijiiii", pwd[65] = "iiiijijijikkkkki";

    switch (event) {
    case WIFI_EVENT_MODULE_INIT:
        puts("|network_user_callback->WIFI_EVENT_MODULE_INIT\n");

        wifi_default_mode_parm.mode = STA_MODE;

        if (wifi_default_mode_parm.mode <= AP_MODE) {
            strncpy((char *)wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], ssid, sizeof(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE]) - 1);
            strncpy((char *)wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], pwd, sizeof(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        }
        wifi_set_default_mode(&wifi_default_mode_parm, 1, 0);//wifi_default_mode_parm.mode == STA_MODE);
        break;
    case WIFI_EVENT_MODULE_START:
        puts("|network_user_callback->WIFI_EVENT_MODULE_START\n");
        broadcast_ctl(TRUE);
        break;
    case WIFI_EVENT_MODULE_STOP:
        puts("|network_user_callback->WIFI_EVENT_MODULE_STOP\n");
        break;
    case WIFI_EVENT_AP_START:
        printf("|network_user_callback->WIFI_EVENT_AP_START,CH=%d\n", wifi_get_channel());
        break;
    case WIFI_EVENT_AP_STOP:
        puts("|network_user_callback->WIFI_EVENT_AP_STOP\n");
        break;
    case WIFI_EVENT_STA_START:
        puts("|network_user_callback->WIFI_EVENT_STA_START\n");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        puts("|network_user_callback->WIFI_EVENT_MODULE_START_ERR\n");
        break;
    case WIFI_EVENT_STA_STOP:
        puts("|network_user_callback->WIFI_EVENT_STA_STOP\n");
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        puts("|network_user_callback->WIFI_STA_DISCONNECT\n");
        broadcast_ctl(TRUE);
        wifi_conn = FALSE;
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        puts("|network_user_callback->WIFI_STA_SCAN_COMPLETED\n");
        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        printf("|network_user_callback->WIFI_STA_CONNECT_SUCC,CH=%d\r\n", wifi_get_channel());
        wifi_conn = TRUE;
        break;
    case WIFI_EVENT_MP_TEST_START:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_START\n");
        break;
    case WIFI_EVENT_MP_TEST_STOP:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_STOP\n");
        break;
    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        puts("|network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID\n");
        broadcast_ctl(TRUE);
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_SUCC\n");
        breathe_ctl(TRUE);
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT\n");
        broadcast_ctl(TRUE);
        break;
    case WIFI_EVENT_P2P_START:
        puts("|network_user_callback->WIFI_EVENT_P2P_START\n");
        break;
    case WIFI_EVENT_P2P_STOP:
        puts("|network_user_callback->WIFI_EVENT_P2P_STOP\n");
        break;
    case WIFI_EVENT_P2P_GC_DISCONNECTED:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_DISCONNECTED\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_START:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_START\n");
        break;
    case WIFI_EVENT_SMP_CFG_STOP:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_STOP\n");
        break;
    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_COMPLETED:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED\n");
        break;
    case WIFI_EVENT_PM_SUSPEND:
        puts("|network_user_callback->WIFI_EVENT_PM_SUSPEND\n");
        break;
    case WIFI_EVENT_PM_RESUME:
        puts("|network_user_callback->WIFI_EVENT_PM_RESUME\n");
        break;
    case WIFI_EVENT_AP_ON_ASSOC:
        puts("WIFI_EVENT_AP_ON_ASSOC\n");
        break;
    case WIFI_EVENT_AP_ON_DISCONNECTED:
        puts("WIFI_EVENT_AP_ON_DISCONNECTED\n");
        break;
    default:
        break;
    }

    return 0;
}


u8 product_net_main(void)
{
    product_info("\r\n================ENTER PRODUCT BOX MODE================\r\n");
    while (!(comm_ops()->online())) {
        os_time_dly(10);
    }

    comm_ops()->init();
    thread_fork("host_data_handle_task", 10, 1024, 0, NULL, host_data_handle_task, NULL);

    os_sem_create(&asem, 0);
    os_sem_create(&bsem, 0);
    wifi_set_frame_cb(wifi_rx_frame_cb, NULL);
    wifi_set_sta_connect_timeout(20);
    wifi_set_event_callback(wifi_event_callback);
    wifi_on();

    return TRUE;
}


#else


static u8 uvc_id = 0;
static void *camera_sock = NULL;
static u32 camera_width, camera_height, camera_fps;

void uvc_set_id(u8 id)
{
    uvc_id = id;
}


void product_net_camera_info(u32 *width, u32 *height, u32 *fps)
{
    *width  = camera_width;
    *height = camera_height;
    *fps    = camera_fps;
}


static int camera_transmit(void *hdr, u8 *data, u32 size)
{
#define JPEG_HEAD 0xE0FFD8FF
#define JPEG_HEAD1 0xC0FFD8FF
    u32 *type = (u32 *)data;
    struct net_cmd_type cmd = {0};
    u32 *params = (u32 *)cmd.params;

    if (!camera_sock) {
        return 0;
    }

    strcpy(cmd.cmd, NET_CAMERA_FRAME);
    params[0] = size;

    if (*type == JPEG_HEAD || *type == JPEG_HEAD1) {
        //video
        sock_send(camera_sock, &cmd, sizeof(struct net_cmd_type), 0);
        sock_send(camera_sock, data, size, 0);
        putchar('V');
    } else {
        //audio
        putchar('A');
    }

    return size;
}


static void camera_conn_task(void *priv)
{
    u32 opt = 1;
    void *s_sock;
    struct net_cmd_type cmd = {0};
    u32 *params = (u32 *)cmd.params;
    struct sockaddr_in local_addr = {0};
    struct sockaddr_in remote_addr = {0};
    socklen_t len = sizeof(struct sockaddr_in);

    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(CAMERA_PORT);

    if (!(s_sock = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL))) {
        product_err("%s build socket fail\n",  __FILE__);
        return;
    }

    if (sock_setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        product_err("%s sock_setsockopt fail\n", __FILE__);
        return;
    }

    if (sock_bind(s_sock, (struct sockaddr *)&local_addr, sizeof(struct sockaddr))) {
        product_err("%s sock_bind fail\n", __FILE__);
        return;
    }

    if (sock_listen(s_sock, 0x2)) {
        product_err("%s sock_listen fail\n", __FILE__);
        return;
    }

    for (;;) {
        if (!(camera_sock = sock_accept(s_sock, (struct sockaddr *)&remote_addr, &len, NULL, NULL))) {
            product_err("%s socket_accept fail\n",  __FILE__);
        } else {
            product_info("host socket conn succ\n");
            for (;;) {
                if (sock_recvfrom(camera_sock, &cmd, sizeof(struct net_cmd_type), 0, NULL, NULL) == sizeof(struct net_cmd_type)) {
                    if (!strcmp(cmd.cmd, NET_CAMERA_OPEN)) {
                        camera_width  = params[0];
                        camera_height = params[1];
                        camera_fps    = params[2];
                        product_info("net camera : w = %d, h = %d, fps = %d\n", params[0], params[1], params[2]);
                        set_video_rt_cb(camera_transmit, NULL);
                        user_video_rec0_open(uvc_id);
                    } else if (!strcmp(cmd.cmd, NET_CAMERA_CLOSE)) {
                        set_video_rt_cb(NULL, NULL);
                        user_video_rec0_close();
                        sock_unreg(camera_sock);
                        camera_sock = NULL;
                        break;
                    }
                }
            }
        }
    }
}


void camera_conn_init(void)
{
    thread_fork("camera_conn_task", 10, 512, 0, NULL, camera_conn_task, NULL);
}


#endif


#endif


