class ObjectList : public IObjectContainer {
    public:
    struct element_s {
        element_s *prev;
        element_s *next;
        void *object;
    };

    typedef element_s element_t;

    protected:
    element_t *head;
    element_t *tail;
    element_t *current;
    int number;

    public:
    ObjectList(void);
    virtual void Init(void);
    virtual bool Add(void *);
    virtual void * GetFirst(void);
    virtual void * GetNext(void);
    ~ObjectList();
    virtual void Clear(bool);
    virtual int CountElements(void);
    void * RemoveTail(void);
    void * RemoveHead(void);
    bool AddTail(void *);
    bool AddHead(void *);
    virtual bool Remove(void *);
    virtual bool Contains(void *);
    virtual bool IsEmpty(void);
};