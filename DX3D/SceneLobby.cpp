#include "stdafx.h"
#include "SceneLobby.h"
#include "UILobby.h"

SceneLobby::SceneLobby()
{
}

SceneLobby::~SceneLobby()
{
}

void SceneLobby::Init()
{
    UILobby* ul = new UILobby;
    ul->Init();
}

void SceneLobby::Update()
{
}

void SceneLobby::Render()
{
}

void SceneLobby::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
