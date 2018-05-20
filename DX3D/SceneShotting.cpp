#include "stdafx.h"
#include "SceneShotting.h"
#include "Grid.h"

SceneShotting::SceneShotting()
	: m_pGrid(nullptr)
{
}


SceneShotting::~SceneShotting()
{
	SAFE_RELEASE(m_pGrid);
}

void SceneShotting::Init()
{
	m_pGrid = new Grid;
	m_pGrid->Init();
}

void SceneShotting::Update()
{
}

void SceneShotting::Render()
{
	m_pGrid->Render();
}

void SceneShotting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
