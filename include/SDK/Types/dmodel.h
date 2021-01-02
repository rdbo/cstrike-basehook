struct dmodel_t {
    float mins[3];
    float maxs[3];
    float origin[3];
    int headnode[4];
    int visleafs;
    int firstface;
    int numfaces;
};