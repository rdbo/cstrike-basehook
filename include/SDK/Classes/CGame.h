class IGame;

class CGame : public IGame {
    //private:
    public:
    bool m_bActiveApp;
    SDL_Window *m_hSDLWindow;
    SDL_GLContext m_hSDLGLContext;
    bool m_bExpectSyntheticMouseMotion;
    int m_nMouseTargetX;
    int m_nMouseTargetY;
    int m_nWarpDelta;
    bool m_bCursorVisible;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    bool m_bMultiplayer;

    public:
    CGame(void);
    ~CGame();
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
    void AppActivate(bool);
    virtual void SetCursorVisible(bool);
    private:
    void SetActiveApp(bool);
};