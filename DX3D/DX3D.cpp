// DX3D.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DX3D.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DX3D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

   g_pApp->Init();

    MSG msg;

   while (true)
   {
      if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
      {
         if (msg.message == WM_QUIT)
         {
            break;
         }
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
      else
      {
         g_pApp->Update();
         g_pApp->Render();
      }
   }

   g_pApp->Destroy();

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
   WNDCLASS wc;
   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = WndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;
   wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName = NULL;
   wc.lpszClassName = szWindowClass;

   return RegisterClass(&wc);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   const int style = WS_OVERLAPPED | WS_CAPTION | WS_DLGFRAME | WS_SYSMENU;
   const int left = 500;
   const int top = 0;
   const int width = 1280;
   const int height = 720;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, style,
                             left, top, width, height, 
                             nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   RECT rc{ 0, 0, width, height };
   AdjustWindowRect(&rc, style, false);
   SetWindowPos(hWnd, NULL,
                left, top,
                rc.right - rc.left, rc.bottom - rc.top,
                SWP_NOZORDER | SWP_NOMOVE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   g_pApp->WndProc(hWnd, message, wParam, lParam);
   //Alt키 막기용
   if (wParam == SC_KEYMENU && (lParam >> 16) <= 0) return 0;

    switch (message)
    {
   case WM_KEYDOWN:
   {
      switch (wParam)
      {
      case VK_ESCAPE:
      {
         SendMessage(hWnd, WM_DESTROY, 0, 0);
      }
      break;
      }
   }
   break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}