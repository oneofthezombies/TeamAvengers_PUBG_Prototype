#pragma once
#include "IScene.h"

class Ground;
//class PlayerTemp;
class PlayerAni;
class Pistol;
class Bullet;
class SampleUIButtonListener;
class Item;

class SceneShotting : public IScene
{
private:
	Ground*           m_pGround;
	//PlayerTemp*       m_pPlayerTemp;
	PlayerAni*        m_pPlayerAni;
	Pistol*           m_pPistol;
	vector<Bullet*>   m_vecPBullet;
	
	vector<VERTEX_PC> m_vecBaseline; //x, y, z 기준선

    SampleUIButtonListener* m_pSampleUIButtonListener;

public:
	SceneShotting();
	~SceneShotting();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

    void InitSkyBox();
    void InitLight();
    void InitAxises();
    void InitGroundGrid();
    void InitPlayer();
    void InitSamples();

    void RenderAxises();

    void RemoveItemPointer(Item& val);
};

