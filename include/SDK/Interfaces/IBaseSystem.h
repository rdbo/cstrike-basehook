class ObjectList;

class IBaseSystem : public virtual ISystemModule {
  public:
    ~IBaseSystem();
    virtual double GetTime(void);
    virtual unsigned int GetTick(void);
    virtual void SetFPS(float);
    virtual void Printf(char *, ...);
    virtual void DPrintf(char *, ...);
    virtual void RedirectOutput(char *, int);
    virtual IFileSystem * GetFileSystem(void);
    virtual unsigned char * LoadFile(const char *, int *);
    virtual void FreeFile(unsigned char *);
    virtual void SetTitle(char *);
    virtual void SetStatusLine(char *);
    virtual void ShowConsole(bool);
    virtual void LogConsole(char *);
    virtual bool InitVGUI(IVGuiModule *);
    virtual bool RegisterCommand(char *, ISystemModule *, int);
    virtual void GetCommandMatches(char *, ObjectList *);
    virtual void ExecuteString(char *);
    virtual void ExecuteFile(char *);
    virtual void Errorf(char *, ...);
    virtual char * CheckParam(char *);
    virtual bool AddModule(ISystemModule *, char *);
    virtual ISystemModule * GetModule(char *, char *, char *);
    virtual bool RemoveModule(ISystemModule *);
    virtual void Stop(void);
    virtual char * COM_GetBaseDir(void);
};