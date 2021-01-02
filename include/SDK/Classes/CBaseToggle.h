class CBaseToggle : public CBaseAnimating {
  public:
    TOGGLE_STATE m_toggle_state;
    float m_flActivateFinished;
    float m_flMoveDistance;
    float m_flWait;
    float m_flLip;
    float m_flTWidth;
    float m_flTLength;
    Vector m_vecPosition1;
    Vector m_vecPosition2;
    Vector m_vecAngle1;
    Vector m_vecAngle2;
    int m_cTriggersLeft;
    float m_flHeight;
    EHANDLE m_hActivator;
    void (CBaseToggle::*m_pfnCallWhenMoveDone)(CBaseToggle * const);
    Vector m_vecFinalDest;
    Vector m_vecFinalAngle;
    int m_bitsDamageInflict;
    static TYPEDESCRIPTION m_SaveData[];
    string_t m_sMaster;

    virtual void KeyValue(KeyValueData_s *);
    virtual int Save(CSave &);
    virtual int Restore(CRestore &);
    virtual int GetToggleState(void);
    virtual float GetDelay(void);
    void LinearMove(Vector, float);
    void LinearMoveDone(void);
    void AngularMove(Vector, float);
    void AngularMoveDone(void);
    BOOL IsLockedByMaster(void);
    static float AxisValue(int, const Vector &);
    static void AxisDir(entvars_t *);
    static float AxisDelta(int, const Vector &, const Vector &);
};