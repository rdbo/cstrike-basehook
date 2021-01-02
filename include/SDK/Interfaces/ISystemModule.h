class IBaseSystem;

class ISystemModule : public IBaseInterface {
  public:
    ~ISystemModule();
    virtual bool Init(IBaseSystem *, int, char *);
    virtual void RunFrame(double);
    virtual void ReceiveSignal(ISystemModule *, unsigned int, void *);
    virtual void ExecuteCommand(int, char *);
    virtual void RegisterListener(ISystemModule *);
    virtual void RemoveListener(ISystemModule *);
    virtual IBaseSystem * GetSystem(void);
    virtual int GetSerial(void);
    virtual char * GetStatusLine(void);
    virtual char * GetType(void);
    virtual char * GetName(void);
    virtual int GetState(void);
    virtual int GetVersion(void);
    virtual void ShutDown(void);
};