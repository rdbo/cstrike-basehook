struct cmd_t {
    usercmd_t cmd;
    float senttime;
    float receivedtime;
    float frame_lerp;
    qboolean processedfuncs;
    qboolean heldback;
    int sendsize;
};