#include "stdafx.h"
#include "SceneGrid.h"
#include "ColorCube.h"
#include "Grid.h"
#include "Cubeman.h"
#include "Walls.h"
#include "ActionCube.h"
#include "Hexagon.h"
#include "VertexBlending.h"

SceneGrid::SceneGrid()
{
	m_pColorCube = NULL;
	m_pGrid = NULL;
	m_pCubeman = NULL;
	m_pWalls = NULL;
	m_pActionCube = NULL;
	m_pHexagon = NULL;
}


SceneGrid::~SceneGrid()
{
	SAFE_RELEASE(m_pColorCube);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pCubeman);
	SAFE_RELEASE(m_pWalls);
	SAFE_RELEASE(m_pActionCube);
	SAFE_RELEASE(m_pHexagon);

    OnDestructIScene();
}

void SceneGrid::Init()
{
	m_pColorCube = new ColorCube(); m_pColorCube->Init();

	//m_pGrid = new Grid(); m_pGrid->Init();
	//m_pCubeman = new Cubeman(); m_pCubeman->Init();
	//m_pWalls = new Walls(); m_pWalls->Init();
	//m_pActionCube = new ActionCube(); m_pActionCube->Init();
	//m_pHexagon = new Hexagon(); m_pHexagon->Init();

    VertexBlending* vb = new VertexBlending;
    vb->Init();
    AddSimpleDisplayObj(vb);
}

void SceneGrid::Update()
{
	SAFE_UPDATE(m_pColorCube);
	SAFE_UPDATE(m_pCubeman);
	SAFE_UPDATE(m_pActionCube);

    OnUpdateIScene();
}

void SceneGrid::Render()
{
	SAFE_RENDER(m_pColorCube);
	SAFE_RENDER(m_pGrid);
	SAFE_RENDER(m_pCubeman);
	SAFE_RENDER(m_pWalls);
	SAFE_RENDER(m_pActionCube);
	SAFE_RENDER(m_pHexagon);

    OnRenderIScene();
}

void SceneGrid::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
