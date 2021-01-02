typedef struct packet_entities_t {
    int num_entities;
    unsigned char flags[32];
    entity_state_s *entities;
} packet_entities_t;