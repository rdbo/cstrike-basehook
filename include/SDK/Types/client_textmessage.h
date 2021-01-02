typedef struct client_textmessage_s {
    int effect;
    byte r1;
    byte g1;
    byte b1;
    byte a1;
    byte r2;
    byte g2;
    byte b2;
    byte a2;
    float x;
    float y;
    float fadein;
    float fadeout;
    float holdtime;
    float fxtime;
    const char *pName;
    const char *pMessage;
} client_textmessage_t;