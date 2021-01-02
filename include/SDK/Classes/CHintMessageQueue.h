class CBaseEntity;

class CHintMessageQueue {
    private:
    float m_tmMessageEnd;
    //CUtlVector<CHintMessage*> m_messages;
    char m_messages[20]; //padding
    
    /*
    public:
    void Reset(void);
    void Update(CBaseEntity &);
    bool AddMessage(const char *, float, bool, CUtlVector<char const*> *);
    bool IsEmpty(void);
    */
};