typedef struct mnode_s {
    int contents;
    int visframe;
    float minmaxs[6];
    mnode_s *parent;
    mplane_t *plane;
    mnode_s *children[2];
    unsigned short firstsurface;
    unsigned short numsurfaces;
} mnode_t;