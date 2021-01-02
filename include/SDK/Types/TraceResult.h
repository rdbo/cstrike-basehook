struct TraceResult {
    int fAllSolid;
    int fStartSolid;
    int fInOpen;
    int fInWater;
    float flFraction;
    Vector vecEndPos;
    float flPlaneDist;
    Vector vecPlaneNormal;
    edict_t *pHit;
    int iHitgroup;
};