#pragma once
#include "IScene.h"

class Ground;
class PlayerTemp;
class Pistol;
class Bullet;
class SampleUIButtonListner;

class SceneShotting : public IScene
{
private:
	Ground*           m_pGround;
	PlayerTemp*       m_pPlayerTemp;
	Pistol*           m_pPistol;
	vector<Bullet*>   m_vecPBullet;
	
	vector<VERTEX_PC> m_vecBaseline; //x, y, z 기준선

    SampleUIButtonListner* m_pSampleUIButtonListner;

public:
	SceneShotting();
	~SceneShotting();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

