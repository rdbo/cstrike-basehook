class IObjectContainer {
  public:
    ~IObjectContainer();
    virtual void Init(void);
    virtual bool Add(void *);
    virtual bool Remove(void *);
    virtual void Clear(bool);
    virtual void * GetFirst(void);
    virtual void * GetNext(void);
    virtual int CountElements(void);
    virtual bool Contains(void *);
    virtual bool IsEmpty(void);
};