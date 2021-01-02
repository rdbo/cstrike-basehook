typedef struct screenfade_s {
    float fadeSpeed;
    float fadeEnd;
    float fadeTotalEnd;
    float fadeReset;
    byte fader;
    byte fadeg;
    byte fadeb;
    byte fadealpha;
    int fadeFlags;
} screenfade_t;