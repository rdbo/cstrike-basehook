struct CBaseEntity;

class EHANDLE {
    private:
    edict_t *m_pent;
    int m_serialnumber;

    public:
    edict_t * Get(void);
    edict_t * Set(edict_t *);
    operator int(void);
    operator CBaseEntity*(void);
    CBaseEntity * operator=(CBaseEntity *);
    CBaseEntity * operator->(void);
};