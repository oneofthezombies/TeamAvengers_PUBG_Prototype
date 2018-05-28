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
    g_pSoundManager->RepeatPlay(static_cast<int>(SOUND_TAG::Lobby), SOUND_TAG::Lobby);
}

void SceneLobby::Render()
{
}

void SceneLobby::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
