class IVGuiModule : public IBaseInterface {
  public:
    virtual bool Initialize(CreateInterfaceFn *, int);
    virtual bool PostInitialize(CreateInterfaceFn *, int);
    virtual bool Activate(void);
    virtual bool IsValid(void);
    virtual void Deactivate(void);
    virtual void Reactivate(void);
    virtual void Shutdown(void);
    //virtual vgui2::VPANEL GetPanel(void);
    virtual unsigned int GetPanel(void);
    //virtual void SetParent(vgui2::VPANEL);
    virtual void SetParent(unsigned int);
    virtual void RunFrame(void);
};