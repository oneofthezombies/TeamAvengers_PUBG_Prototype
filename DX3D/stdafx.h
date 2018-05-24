#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#define NOMINMAX
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <cassert>
#include <atlstr.h>

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;

#include <list>
using std::list;

#include <string>
using std::to_string;
using std::string;

#include <fstream>

#include <chrono>
using std::chrono::system_clock;
using std::chrono::duration;

#include <unordered_set>
using std::unordered_multiset;
using std::unordered_set;

#include <iterator>
using std::advance;
using std::next;
using std::prev;

#include <iostream>
using std::cout;
using std::endl;

#include <deque>
using std::deque;

#include <unordered_map>
using std::unordered_multimap;
using std::unordered_map;

#include <limits>
using std::numeric_limits;

#include <utility>
using std::make_pair;
using std::pair;

#include <type_traits>
using std::is_base_of_v;
using std::enable_if_t;

#include <functional>
using std::hash;

#include <bitset>
using std::bitset;

#include <typeindex>
using std::type_index;

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;

#include "Application.h"
#include "DeviceManager.h"
#include "D3DUtility.h"
#include "BaseObject.h"
#include "GlobalDefinition.h"
#include "IMap.h"
#include "IUnitObject.h"
#include "IAction.h"
#include "ICamera.h"
#include "Debug.h"
#include "ObjManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "FontManager.h"
#include "CameraManager.h"
#include "MapManager.h"
#include "KeyboardManager.h"
#include "keyManager.h"
#include "IScene.h"
#include "UIManager.h"
#include "CollisionManager.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif
#define D3DX_DEBUG