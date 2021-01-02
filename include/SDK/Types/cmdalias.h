typedef struct cmdalias_s {
    cmdalias_s *next;
    char name[32];
    char *value;
} cmdalias_t;