struct sentenceEntry_s;

struct sentenceEntry_ {
    char *data;
    sentenceEntry_s *nextEntry;
    qboolean isGlobal;
    unsigned int index;
};

struct sentenceEntry_s : public sentenceEntry_ {  };