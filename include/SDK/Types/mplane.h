typedef struct mplane_s {
    vec3_t normal;
    float dist;
    byte type;
    byte signbits;
    byte pad[2];
} mplane_t;