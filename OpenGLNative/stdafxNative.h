// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>		// Header File For Windows

#include <glm.hpp>
#include <gtx\transform.hpp>

#include <glew.h>

#include <unordered_map>
#include <memory>

//We do not need to include either of these headers because of glew

//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library
