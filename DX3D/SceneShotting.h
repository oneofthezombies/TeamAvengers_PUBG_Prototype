#pragma once
#include "IScene.h"

class Ground;
//class PlayerTemp;
class PlayerAni;
class Pistol;
class Bullet;
class SampleUIButtonListner;

class SceneShotting : public IScene
{
private:
	Ground*           m_pGround;
	//PlayerTemp*       m_pPlayerTemp;
	PlayerAni*        m_pPlayerAni;
	Pistol*           m_pPistol;
	vector<Bullet*>   m_vecPBullet;
	
	vector<VERTEX_PC> m_vecBaseline; //x, y, z 기준선

    SampleUIButtonListner* m_pSampleUIButtonListner;

public:
    //잠시 test sample    //JH---------
    vector<VERTEX_PC> vecVertex_sample;
    vector<VERTEX_PC>& GetWallVertex()
    {
        return vecVertex_sample;
    }
    //---------------

public:
	SceneShotting();
	~SceneShotting();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

