struct MonsterEvent_t;

class CBaseAnimating : public CBaseDelay {
  public:
    static TYPEDESCRIPTION m_SaveData[];
    float m_flFrameRate;
    float m_flGroundSpeed;
    float m_flLastEventCheck;
    BOOL m_fSequenceFinished;
    BOOL m_fSequenceLoops;

    virtual int Save(CSave &);
    virtual int Restore(CRestore &);
    float StudioFrameAdvance(float);
    BOOL GetSequenceFlags(void);
    int LookupActivity(int);
    int LookupActivityHeaviest(int);
    int LookupSequence(const char *);
    void ResetSequenceInfo(void);
    void DispatchAnimEvents(float);
    virtual void HandleAnimEvent(MonsterEvent_t *);
    float SetBoneController(int, float);
    void InitBoneControllers(void);
    float SetBlending(int, float);
    void GetBonePosition(int, Vector &, Vector &);
    void GetAutomovement(Vector &, Vector &, float);
    int FindTransition(int, int, int *);
    void GetAttachment(int, Vector &, Vector &);
    void SetBodygroup(int, int);
    int GetBodygroup(int);
    int ExtractBbox(int, float *, float *);
    void SetSequenceBox(void);
};