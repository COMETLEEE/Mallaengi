#pragma once
// 이 헤더 파일은 Client Project의 Pre-Compiled Header입니다.

// Include Engine Static Library

//Sound
#include "../Library/SoundManager.h"

#pragma comment(lib, "..\\..\\Output\\Engine.lib")
#pragma comment(lib, "..\\..\\Output\\Library.lib")

// Include Engine Pre-Compiled Header
#include "..\\Engine\\pch.h"

// C++
#include <functional>

// In-Game
#include "Game.h"

// 타일 정보를 컨트롤하는 Define
#define TILE_WIDTH 80
#define TILE_HEIGHT 77

// 카메라 줌 비율을 고려해서 UI들의 위치를 조절합니다.
#define CAMERA_ZOOM 0.7f

#define _AFXDLL
#undef _WINDOWS_
#include <afx.h>

#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif