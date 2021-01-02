struct latchedvars_t {
    float prevanimtime;
    float sequencetime;
    unsigned char prevseqblending[2];
    vec3_t prevorigin;
    vec3_t prevangles;
    int prevsequence;
    float prevframe;
    unsigned char prevcontroller[4];
    unsigned char prevblending[2];
};