#ifndef __UI_NEW_H__
#define __UI_NEW_H__

typedef enum {
    GUI_MSG_ACCESS_GET = 0,
    GUI_MSG_ACCESS_SET,
    GUI_MSG_SUBSCRIBE,
    GUI_MSG_UNSUBSCRIBE,
} gui_msg_action_t;

typedef union {
    void *value_ptr;
    int value_int;
    struct {
        void *ptr;
        int len;
    } value_array;
} gui_msg_data_t;

struct ui_module_event_handler {
    int msg_id;
    void (*onchange)(gui_msg_action_t change_event, gui_msg_data_t *data);
};


extern const struct ui_module_event_handler ui_module_event_handler_begin[], ui_module_event_handler_end[];


#define REGISTER_UI_MODULE_EVENT_HANDLER(_msg_id) \
        static const struct ui_module_event_handler ui_module_event_handler_##_msg_id \
            sec(.ui_module_event_handler) __attribute__((used)) = { \
                                .msg_id = _msg_id,




#endif


