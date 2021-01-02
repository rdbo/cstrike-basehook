typedef struct consistency_s {
    char *filename;
    int issound;
    int orig_index;
    int value;
    int check_type;
    float mins[3];
    float maxs[3];
} consistency_t;