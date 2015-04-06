// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <gdiplus.h>
#include "FPSCounter.h"
#include "GameDef.h"

#include "Maths.h"
#include "Common.h"
#include "Render.h"
using namespace Common;

#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)