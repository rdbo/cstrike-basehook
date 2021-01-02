#include <SDL2/SDL.h>

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) && !defined(linux))
#include <Windows.h>
#else
typedef void* HWND;
typedef int   BOOL;
typedef unsigned long ULONG;
typedef int HSPRITE;
#endif

typedef float vec3_t[3];
typedef unsigned int string_t;
typedef float vec_t;
typedef int int32;
typedef int qboolean;
typedef unsigned char byte;
typedef unsigned long long uint64;