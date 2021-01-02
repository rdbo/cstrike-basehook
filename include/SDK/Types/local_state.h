typedef struct local_state_s {
    entity_state_t playerstate;
    clientdata_t client;
    weapon_data_s weapondata[64];
} local_state_t;