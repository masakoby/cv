#define WINDOWS
//#define LINUX


#ifdef LINUX
#include <experimental/filesystem>
#endif
#ifdef WINDOWS
#include <direct.h>
#endif
