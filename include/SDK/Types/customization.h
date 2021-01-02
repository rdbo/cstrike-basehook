typedef struct customization_s {
    qboolean bInUse;
    resource_t resource;
    qboolean bTranslated;
    int nUserData1;
    int nUserData2;
    void *pInfo;
    void *pBuffer;
    customization_s *pNext;
} customization_t;