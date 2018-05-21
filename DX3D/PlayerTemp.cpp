#include "stdafx.h"
#include "PlayerTemp.h"
#include "Pistol.h"

PlayerTemp::PlayerTemp()
	: m_pPlayerMesh(nullptr)
	, m_pPistol(nullptr)
	, m_velocity(5.f)
	, m_isRun(false)
{
}

PlayerTemp::~PlayerTemp()
{
	SAFE_RELEASE(m_pPlayerMesh);
	SAFE_RELEASE(m_pPistol);
}

void PlayerTemp::Init()
{
	m_pos = D3DXVECTOR3(0.f, 3.f, -20.f);                          //일단 하드코딩으로 위치 박음
	D3DXCreateBox(g_pDevice, 2.f, 6.f, 2.f, &m_pPlayerMesh, NULL); //임시 플레이어 메쉬 생성 (임시로 박스 모양)
	
	/* 총 Init */
	m_pPistol = new Pistol(10, 0.4f, 5.f, 0.7f, -D3DXToRadian(90));
	m_pPistol->Init();
}

void PlayerTemp::Update()
{
	float deltaTime = g_pTimeManager->GetDeltaTime();
	float distance = deltaTime * m_velocity;

	/* 이동 ASDW */
	// 맵 구역 안에 있을 때만 움직인다 
	if (g_pKeyManager->IsStayKeyDown('A')) //왼쪽
	{
		if (m_pos.x - distance >= -5.f)
			m_pos.x -= distance;
	}
	if (g_pKeyManager->IsStayKeyDown('D')) //오른쪽
	{
		if (m_pos.x + distance <= 5.f)
			m_pos.x += distance;
	}
	if (g_pKeyManager->IsStayKeyDown('W')) //위쪽
	{
		if (m_pos.z + distance <= 20.f)
			m_pos.z += distance;
	}
	if (g_pKeyManager->IsStayKeyDown('S')) //아래쪽
	{
		if (m_pos.z - distance >= -20.f)
			m_pos.z -= distance;
	}

	//총 위치 업데이트
	m_pPistol->SetPosition(&D3DXVECTOR3(m_pos.x, m_pos.y + 1.f, m_pos.z + 2.f)); //플레이어보다 살짝 위, 살짝 앞

	/* 총쏘기 SPACE */ //TODO: 마우스 왼쪽 버튼으로 바꿔야함!!
	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
	{
		m_pPistol->Fire();
	}

	/* 장전 R */
	if (g_pKeyManager->IsOnceKeyDown('R'))
	{
		std::cout << "장전!" << std::endl;
		m_pPistol->Load();
	}

	//변환행렬 재설정
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = m_matT;

	/* 총 Update */
	SAFE_UPDATE(m_pPistol);
}

void PlayerTemp::Render()
{
	const auto dv = g_pDevice;
	dv->SetRenderState(D3DRS_LIGHTING, false);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	dv->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pPlayerMesh->DrawSubset(0);

	dv->SetRenderState(D3DRS_LIGHTING, true);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	/* 총 Render */
	SAFE_RENDER(m_pPistol);
}

