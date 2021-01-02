typedef struct usercmd_s {
    short lerp_msec;
    byte msec;
    vec3_t viewangles;
    float forwardmove;
    float sidemove;
    float upmove;
    byte lightlevel;
    unsigned short buttons;
    byte impulse;
    byte weaponselect;
    int impact_index;
    vec3_t impact_position;
} usercmd_t;