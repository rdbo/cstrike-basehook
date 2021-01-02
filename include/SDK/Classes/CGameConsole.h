class IGameConsole;
class CGameConsoleDialog;

class CGameConsole : public IGameConsole {
    private:
    bool m_bInitialized;
    CGameConsoleDialog *m_pConsole;

    public:
    CGameConsole(void);
    ~CGameConsole();
    virtual void Initialize(void);
    virtual void Activate(void);
    virtual void Hide(void);
    virtual void Clear(void);
    virtual void Printf(const char *, ...);
    virtual void DPrintf(const char *, ...);
    virtual bool IsConsoleVisible(void);
    void ActivateDelayed(float);
    virtual void SetParent(int);
  private:
    static void OnCmdCondump(void);
};