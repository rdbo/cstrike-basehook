typedef struct mleaf_s {
    int contents;
    int visframe;
    float minmaxs[6];
    mnode_s *parent;
    byte *compressed_vis;
    efrag_s *efrags;
    msurface_t **firstmarksurface;
    int nummarksurfaces;
    int key;
    unsigned char ambient_sound_level[4];
} mleaf_t;