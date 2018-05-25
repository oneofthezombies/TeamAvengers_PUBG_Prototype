#pragma once
#include "IScene.h"

class Ground;
class PlayerAni;
class Gun;
class Bullet;
class SampleUIButtonListener;
class Item;

class SceneShotting : public IScene
{
private:
	Ground*           m_pGround;
	PlayerAni*        m_pPlayerAni;
	Gun*              m_pPistol;
	Gun*              m_pRifle;
	vector<Bullet*>   m_vecPBulletForPistol; //���ѿ� ����
	vector<Bullet*>   m_vecPBulletForRifle;  //���ѿ� �Ѿ�
	
	vector<VERTEX_PC> m_vecBaseline; //x, y, z ���ؼ�

    SampleUIButtonListener* m_pSampleUIButtonListener;

public:
	SceneShotting();
	~SceneShotting();

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

