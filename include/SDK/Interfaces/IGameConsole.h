class IBaseInterface;

class IGameConsole : public IBaseInterface {
    public:
    virtual void Activate(void);
    virtual void Initialize(void);
    virtual void Hide(void);
    virtual void Clear(void);
    virtual bool IsConsoleVisible(void);
    virtual void Printf(const char *, ...);
    virtual void DPrintf(const char *, ...);
    virtual void SetParent(int);
};