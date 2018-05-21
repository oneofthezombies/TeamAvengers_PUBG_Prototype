#pragma once
#include "IScene.h"

class Ground;
class Gun;
class SceneShotting : public IScene
{
private:
	Ground*           m_pGround;
	Gun*              m_pGun;
	
	vector<VERTEX_PC> m_vecBaseline; //x, y, z 기준선

public:
	SceneShotting();
	~SceneShotting();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

