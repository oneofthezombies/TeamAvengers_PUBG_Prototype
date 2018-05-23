#include "stdafx.h"
#include "SceneManager.h"
#include "IScene.h"
#include "SceneGrid.h"
#include "SceneObjMap.h"
#include "SceneHeightmap.h"
#include "SceneTest.h"
#include "SceneShotting.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_vecScene.push_back(new SceneGrid());
	m_vecScene.push_back(new SceneObjMap());
	m_vecScene.push_back(new SceneHeightmap());
	m_vecScene.push_back(new SceneTest());
	m_vecScene.push_back(new SceneShotting());

	//SetCurrentScene(SCENE_GRID);
	SetCurrentScene(SCENE_OBJMAP);
	//SetCurrentScene(SCENE_HEIGHTMAP);
	//SetCurrentScene(SCENE_TEST);
	//SetCurrentScene(SCENE_SHOTTING);
}

void SceneManager::Destroy()
{
	for (auto p : m_vecScene)
	{
		SAFE_RELEASE(p);
	}
}

void SceneManager::Update()
{
	SAFE_UPDATE(m_pCurrScene);
}

void SceneManager::Render()
{
	SAFE_RENDER(m_pCurrScene);
}

void SceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrScene)
		m_pCurrScene->WndProc(hWnd, message, wParam, lParam);
}

void SceneManager::SetCurrentScene(size_t index)
{
	if (index >= m_vecScene.size()) return;

	IScene* pScene = m_vecScene[index];
	if (pScene)
	{
		pScene->Init();
		m_pCurrScene = pScene;
	}
}
