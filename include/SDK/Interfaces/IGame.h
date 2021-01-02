class IGame {
    public:
    ~IGame();
    virtual bool Init(void *);
    virtual bool Shutdown(void);
    virtual bool CreateGameWindow(void);
    virtual void SleepUntilInput(int);
    virtual HWND GetMainWindow(void);
    virtual HWND * GetMainWindowAddress(void);
    virtual void SetWindowXY(int, int);
    virtual void SetWindowSize(int, int);
    virtual void GetWindowRect(int *, int *, int *, int *);
    virtual bool IsActiveApp(void);
    virtual bool IsMultiplayer(void);
    virtual void PlayStartupVideos(void);
    virtual void PlayAVIAndWait(const char *);
    virtual void SetCursorVisible(bool);
};