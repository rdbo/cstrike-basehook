typedef struct resource_s {
    char szFileName[64];
    resourcetype_t type;
    int nIndex;
    int nDownloadSize;
    unsigned char ucFlags;
    unsigned char rgucMD5_hash[16];
    unsigned char playernum;
    unsigned char rguc_reserved[32];
    resource_s *pNext;
    resource_s *pPrev;
} resource_t;