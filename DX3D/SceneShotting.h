#pragma once
#include "IScene.h"

class Grid;
class SceneShotting : public IScene
{
private:
	Grid*  m_pGrid;

public:
	SceneShotting();
	~SceneShotting();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

