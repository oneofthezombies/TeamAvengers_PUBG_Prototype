#include "stdafx.h"
#include "SceneShotting.h"
#include "Ground.h"
#include "Gun.h"

SceneShotting::SceneShotting()
	: m_pGround(nullptr)
	, m_pGun(nullptr)
{
}


SceneShotting::~SceneShotting()
{
	SAFE_RELEASE(m_pGround);
	SAFE_RELEASE(m_pGun);
}

void SceneShotting::Init()
{
	//x, y, z ±âÁØ¼±
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

	//¹Ù´Ú
	m_pGround = new Ground(6, 20, 2.f);
	m_pGround->Init();
	AddSimpleDisplayObj(m_pGround);

	//ÃÑ
	m_pGun = new Gun(10, 0.4f, 5.f, 0.7f, -D3DXToRadian(90));
	m_pGun->Init();
	AddSimpleDisplayObj(m_pGun);
}

void SceneShotting::Update()
{
	OnUpdateIScene();
}

void SceneShotting::Render()
{
	OnRenderIScene();
}

void SceneShotting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
