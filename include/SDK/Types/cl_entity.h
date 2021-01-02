struct model_s;
struct efrag_s;

typedef struct cl_entity_s {
    int index;
    qboolean player;
    entity_state_t baseline;
    entity_state_t prevstate;
    entity_state_t curstate;
    int current_position;
    position_history_t ph[64];
    mouth_t mouth;
    latchedvars_t latched;
    float lastmove;
    vec3_t origin;
    vec3_t angles;
    float attachment[4][3];
    int trivial_accept;
    model_s *model;
    efrag_s *efrag;
    mnode_s *topnode;
    float syncbase;
    int visframe;
    colorVec cvFloorColor;
} cl_entity_t;