#pragma once
#include "IScene.h"

class ColorCube;
class Grid;
class Cubeman;
class Walls;
class ActionCube;
class Hexagon;

class SceneGrid :
	public IScene
{
	ColorCube*	m_pColorCube;
	Grid*		m_pGrid;
	Cubeman*	m_pCubeman;
	Walls*		m_pWalls;
	ActionCube*	m_pActionCube;
	Hexagon*	m_pHexagon;

public:
	SceneGrid();
	~SceneGrid();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

