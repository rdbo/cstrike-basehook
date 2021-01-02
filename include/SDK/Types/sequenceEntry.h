struct sequenceEntry_s;

struct sequenceEntry_ {
    char *fileName;
    char *entryName;
    sequenceCommandLine_s *firstCommand;
    sequenceEntry_s *nextEntry;
    qboolean isGlobal;
};

struct sequenceEntry_s : public sequenceEntry_ {  };