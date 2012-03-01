#include "assert.h"
#include "tchar.h"
#include "string.h"
#include "windows.h"
#include <QtCore>

#if defined(DEBUG) || defined(_DEBUG)
#define X_ASSERT(x) assert(x)
#else
#define X_ASSERT(X)
#endif