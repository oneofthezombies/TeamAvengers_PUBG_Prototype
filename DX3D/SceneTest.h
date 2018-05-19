#pragma once
#include "IScene.h"
class Grid;
class SceneTest :
	public IScene
{
public:
	Grid * m_pGrid;
	SceneTest();
	~SceneTest();

	// Inherited via IScene
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

