class IEngine;

class CEngine : public IEngine {
    private:
    int m_nQuitting;
    int m_nDLLState;
    int m_nSubState;
    double m_fCurTime;
    double m_fFrameTime;
    double m_fOldTime;
    bool m_bTrapMode;
    bool m_bDoneTrapping;
    int m_nTrapKey;
    int m_nTrapButtons;

    public:
    CEngine(void);
    ~CEngine();
    virtual bool Load(bool, char *, char *);
    virtual void Unload(void);
    virtual void SetState(int);
    virtual int GetState(void);
    virtual void SetSubState(int);
    virtual int GetSubState(void);
    virtual int Frame(void);
    virtual double GetFrameTime(void);
    virtual double GetCurTime(void);
    virtual void TrapKey_Event(int, bool);
    virtual void TrapMouse_Event(int, bool);
    virtual void StartTrapMode(void);
    virtual bool IsTrapping(void);
    virtual bool CheckDoneTrapping(int &, int &);
    virtual int GetQuitting(void);
    virtual void SetQuitting(int);
};