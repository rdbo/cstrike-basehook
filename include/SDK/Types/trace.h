struct trace_t {
    qboolean allsolid;
    qboolean startsolid;
    qboolean inopen;
    qboolean inwater;
    float fraction;
    vec3_t endpos;
    plane_t plane;
    edict_t *ent;
    int hitgroup;
};