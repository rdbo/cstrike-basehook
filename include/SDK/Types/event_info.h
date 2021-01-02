typedef struct event_info_s {
    unsigned short index;
    short packet_index;
    short entity_index;
    float fire_time;
    event_args_t args;
    int flags;
} event_info_t;