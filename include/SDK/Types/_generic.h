class IBaseInterface;

typedef struct rect_s { int left; int right; int top; int bottom; } wrect_t;
struct color24 { byte r; byte g; byte b; };
struct colorVec { unsigned int r; unsigned int g; unsigned int b; unsigned int a; };
typedef unsigned int CRC32_t;
typedef int EOFFSET;
typedef IBaseInterface*(*CreateInterfaceFn)(const char*, int *);