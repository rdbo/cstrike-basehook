struct sequenceCommandLine_s;

struct sequenceCommandLine_ {
    int commandType;
    client_textmessage_t clientMessage;
    char *speakerName;
    char *listenerName;
    char *soundFileName;
    char *sentenceName;
    char *fireTargetNames;
    char *killTargetNames;
    float delay;
    int repeatCount;
    int textChannel;
    int modifierBitField;
    sequenceCommandLine_s *nextCommandLine;
};

struct sequenceCommandLine_s : public sequenceCommandLine_ { };