#pragma once
#include "IScene.h"

//총알
struct Bullet //총알마다 개별적으로 가지고 있는 속성
{
	int life;
	D3DXVECTOR3 pos;
	D3DXMATRIXA16 matTranslation;
};

struct BulletProperty //모든 총알이 공통적으로 가지고 있는 속성
{
	float bulletVelocity;
	float scale;
	D3DXMATRIXA16 matScale;
};

//플레이어 -> 무기
struct Player
{
	int life;
	D3DXVECTOR3 pos;
	float scale;
	float rotY;
	float velocity;

	//총알 관련
	DWORD bulletFireTime;
	DWORD oldBulletFireTime;

	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matScale;
	D3DXMATRIXA16 matRotY;
	D3DXMATRIXA16 matTranslation;
};

class Ground;
class SceneShotting : public IScene
{
private:
	Ground*           m_pGround;

	vector<VERTEX_PC> m_vecBaseline; //x, y, z 기준선
	LPD3DXMESH        m_pTeapotMesh; //플레이어를 출력하기 위한 매쉬
	LPD3DXMESH        m_pBulletMesh; //총알(원기둥)을 출력하기 위한 매쉬

	Player            m_player;
	BulletProperty    m_bulletProperty;
	Bullet            m_bullet[10]; //한 화면에 미사일의 개수를 10개로 제한한다

public:
	SceneShotting();
	~SceneShotting();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

