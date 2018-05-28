#pragma once
#include "IScene.h"

class Ground;
class PlayerAni;
class Gun;
class Bullet;
class SampleUIButtonListener;
class Item;
class HeightMap;
class CubemanBarrack;

class SceneShotting : public IScene
{
private:
    HeightMap*        m_pHeightMap;
	Ground*           m_pGround;
	PlayerAni*        m_pPlayerAni;
	Gun*              m_pPistol;
	Gun*              m_pRifle;
	vector<Bullet*>   m_vecPBulletForPistol; //±ÇÃÑ¿ë ÃÑ¾Ë
	vector<Bullet*>   m_vecPBulletForRifle;  //¼ÒÃÑ¿ë ÃÑ¾Ë
	
	vector<VERTEX_PC> m_vecBaseline; //x, y, z ±âÁØ¼±

    SampleUIButtonListener* m_pSampleUIButtonListener;

    CubemanBarrack* m_cubemanBarrack;

public:
    //Àá½Ã test sample    //JH---------
    vector<VERTEX_PC> vecVertex_sample;
    vector<VERTEX_PC>& GetWallVertex()
    {
        return vecVertex_sample;
    }
    //---------------

public:
	SceneShotting();
	~SceneShotting();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

    void InitSkyBox();
    void InitLight();
    void InitHeightMap();
    void InitAxises();
    void InitGroundGrid();
    void InitPlayer();
    void InitSamples();

    void RenderAxises();

    void RemoveItemPointer(Item& val);
};

