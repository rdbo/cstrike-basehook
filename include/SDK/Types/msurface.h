typedef struct msurface_s {
    int visframe;
    int dlightframe;
    int dlightbits;
    mplane_t *plane;
    int flags;
    int firstedge;
    int numedges;
    surfcache_s *cachespots[4];
    short texturemins[2];
    short extents[2];
    mtexinfo_t *texinfo;
    byte styles[4];
    color24 *samples;
    decal_t *pdecals;
} msurface_t;