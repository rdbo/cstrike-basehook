class IBaseUI : public IBaseInterface {
  public:
    virtual void Initialize(CreateInterfaceFn *, int);
    virtual void Start(cl_enginefuncs_s *, int);
    virtual void Shutdown(void);
    virtual int Key_Event(int, int, const char *);
    virtual void CallEngineSurfaceAppHandler(void *, void *);
    virtual void Paint(int, int, int, int);
    virtual void HideGameUI(void);
    virtual void ActivateGameUI(void);
    virtual void HideConsole(void);
    virtual void ShowConsole(void);
};