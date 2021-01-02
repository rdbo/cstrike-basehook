typedef struct dlight_s {
    vec3_t origin;
    float radius;
    color24 color;
    float die;
    float decay;
    float minlight;
    int key;
    qboolean dark;
} dlight_t;