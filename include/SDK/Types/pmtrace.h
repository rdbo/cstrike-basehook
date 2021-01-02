typedef struct pmtrace_s {
    qboolean allsolid;
    qboolean startsolid;
    qboolean inopen;
    qboolean inwater;
    float fraction;
    vec3_t endpos;
    pmplane_t plane;
    int ent;
    vec3_t deltavelocity;
    int hitgroup;
} pmtrace_t;