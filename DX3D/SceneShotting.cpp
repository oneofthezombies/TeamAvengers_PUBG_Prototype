#include "stdafx.h"
#include "SceneShotting.h"
#include "Ground.h"
#include "PlayerTemp.h"
#include "Pistol.h"
#include "Bullet.h"

SceneShotting::SceneShotting()
	: m_pGround(nullptr)
	, m_pPlayerTemp(nullptr)
    , m_pPistol(nullptr)
{
}


SceneShotting::~SceneShotting()
{
	OnDestructIScene();
}

void SceneShotting::Init()
{
	//x, y, z 기준선
	D3DCOLOR c;
	float halfLength = 15.f;
	c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(-halfLength, 0.0f, 0.0f), c));
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(halfLength, 0.0f, 0.0f), c));
	c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, -halfLength, 0.0f), c));
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, halfLength, 0.0f), c));
	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, -halfLength), c));
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, halfLength), c));

	//바닥
	m_pGround = new Ground(6, 20, 2.f);
	m_pGround->Init();
	AddSimpleDisplayObj(m_pGround);

	//임시플레이어
	m_pPlayerTemp = new PlayerTemp();
	m_pPlayerTemp->Init();
	AddSimpleDisplayObj(m_pPlayerTemp);

	//권총
	m_pPistol = new Pistol(10, 0.4f, 5.f, 0.7f, -D3DXToRadian(90));
	m_pPistol->Init();
	AddSimpleDisplayObj(m_pPistol);

	//총알 10개 생성
	m_vecPBullet.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		Bullet* bullet = new Bullet(0.08f, 10.f);
		bullet->Init();
		m_vecPBullet.push_back(bullet);
		AddSimpleDisplayObj(bullet);
	}

	//총이랑 총알먹기 //포인터에 대한 소유권을 명확히 해야한다
	m_pPlayerTemp->PutItemInInventory(m_pPistol);
	m_pPistol = nullptr;
	for (auto bullet : m_vecPBullet)
	{ 
		m_pPlayerTemp->PutItemInInventory(bullet);
	}
	m_vecPBullet.clear();
}

void SceneShotting::Update()
{
	OnUpdateIScene();
}

void SceneShotting::Render()
{
	OnRenderIScene();


	//x, y, z 기준선 그리기 
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);

	const auto dv = g_pDevice;
	dv->SetRenderState(D3DRS_LIGHTING, false);
	
	dv->SetTransform(D3DTS_WORLD, &matI);
	dv->SetFVF(VERTEX_PC::FVF);
	dv->DrawPrimitiveUP(D3DPT_LINELIST, m_vecBaseline.size() / 2, &m_vecBaseline[0], sizeof(VERTEX_PC));
	
	dv->SetRenderState(D3DRS_LIGHTING, true);
}

void SceneShotting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
