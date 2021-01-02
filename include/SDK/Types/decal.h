struct msurface_s;

typedef struct decal_s {
    decal_s *pnext;
    msurface_s *psurface;
    float dx;
    float dy;
    float scale;
    short texture;
    short flags;
    short entityIndex;
} decal_t;