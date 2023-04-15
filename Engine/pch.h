// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 이 게임 내부에서 0과 같다는 의미로써의 수치입니다.
#define EPSILON 0.001f

// 일반화 포기하겠습니다.
//#ifdef UNICODE
//#define TSTRING std::wstring
//#else
//#define TSTRING std::string
//#endif

// Direct2D
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

// Direct2D API
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

// C RunTime Header Files
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#include <cwchar>
#include <tchar.h>
#include <cmath>
#include <cassert>

// C++ / STL
#include <memory>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

// Utils
#include "Vector2D.h"

// Engine 내부 정보 제공
#include "Engine.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "Collision.h"
#include "AABBCollision.h"
#include "CircleCollision.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Renderer.h"

#endif //PCH_H

// 인터페이스의 릴리즈와 에러 핸들링을 위한 함수들을 선언 및 정의합니다.
template<class Interface>
inline void SafeRelease(Interface** _ppInterfaceToRelease)
{
	if (*_ppInterfaceToRelease != NULL)
	{
		(*_ppInterfaceToRelease)->Release();

		(*_ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
#if defined(DEBUG) || defined(_DEBUG)
#define Assert(b) if (!(b)) {OutputDebugString("Assert : " #b "\n");}
#else
#define Assert(b)
#endif // DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#define _AFXDLL
#undef _WINDOWS_
#include <afx.h>

#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif