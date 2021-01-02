struct mleaf_s;

typedef struct efrag_s {
    mleaf_s *leaf;
    efrag_s *leafnext;
    cl_entity_s *entity;
    efrag_s *entnext;
} efrag_t;