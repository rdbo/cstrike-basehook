struct CBaseEntity;

class CBaseDelay : public CBaseEntity {
  public:
    float m_flDelay;
    int m_iszKillTarget;
    static TYPEDESCRIPTION m_SaveData[];

    virtual void KeyValue(KeyValueData_s *);
    virtual int Save(CSave &);
    virtual int Restore(CRestore &);
    void SUB_UseTargets(CBaseEntity *, USE_TYPE, float);
    void DelayThink(void);
};