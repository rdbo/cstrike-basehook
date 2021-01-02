typedef struct texture_s {
    char name[16];
    unsigned int width;
    unsigned int height;
    int anim_total;
    int anim_min;
    int anim_max;
    texture_s *anim_next;
    texture_s *alternate_anims;
    unsigned int offsets[4];
    unsigned int paloffset;
} texture_t;