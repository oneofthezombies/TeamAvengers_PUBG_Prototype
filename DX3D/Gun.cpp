#include "stdafx.h"
#include "Gun.h"
#include "Bullet.h"

Gun::Gun(int bulletNum, int bulletFireCoolTime, float velocity, float scale, float rotY)
	: m_bulletNum(bulletNum)
	, m_bulletFireCoolTime(bulletFireCoolTime) //0.4f
	, m_velocity(velocity) //5.f;
	, m_scale(scale)       //0.7f
	, m_rotY(rotY)         //-D3DXToRadian(90)
	, m_pGunMesh(nullptr)
{
}

Gun::~Gun()
{
	/* 총알 Release */
	for (auto bullet : m_vecBullet)
	{
		SAFE_RELEASE(bullet);
	}

	SAFE_RELEASE(m_pGunMesh);
}

void Gun::Init()
{
	m_pos = D3DXVECTOR3(0.f, 2.f, -9 * 2.f);        //일단 하드코딩으로 위치 박음

	D3DXCreateTeapot(g_pDevice, &m_pGunMesh, NULL); //총 메쉬 생성 (임시로 주전자 모양)
	m_bulletFireCoolDown = m_bulletFireCoolTime;    //쿨다운을 쿨타임으로 초기화

	D3DXMatrixScaling(&m_matS, m_scale, m_scale, m_scale);
	D3DXMatrixRotationY(&m_matRotY, m_rotY);
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);

	//최대 총알 장전 개수 만큼 (우선 총알 아이템이 없어도 무한하게 장전하게끔 셋팅)
	for (int i = 0; i < m_bulletNum; ++i)
	{
		Bullet* bullet = new Bullet(0.08f, 10.f);
		/* 총알 Init */
		bullet->Init();
		m_vecBullet.emplace_back(bullet);
	}
}

void Gun::Update()
{
	float deltaTime = g_pTimeManager->GetDeltaTime(); //프레임당 초단위 시간간격
	float distance = deltaTime * m_velocity;          //이동거리

	// 맵 구역 안에 있을 때만 움직인다 (임시로 누르고 있으면 계속 발사되게 해놓음)
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

	//총알 발사
	m_bulletFireCoolDown -= deltaTime;
	if (m_bulletFireCoolDown <= 0.f) m_bulletFireCoolDown = 0.f;

	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
	{
		if (m_bulletFireCoolDown <= 0.f)
		{
			for (auto bullet : m_vecBullet)
			{
				if (bullet->GetIsFire() == false) //소멸된 미사일 중에서 하나를 살린다
				{
					bullet->SetIsFire(true);
					bullet->SetPosition(&D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z + 1.f)); //플레이어 위치에서 발사하되, 플레이어보다 약간 앞쪽에서 발사
					break; //미사일 하나만 날리고 반복문 탈출
				}
			}
			m_bulletFireCoolDown = m_bulletFireCoolTime;
		}
	}

	//변환행렬
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = m_matS * m_matRotY * m_matT;

	/* 총알 Update */
	for (auto bullet : m_vecBullet)
	{
		bullet->Update();
	}
}

void Gun::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGunMesh->DrawSubset(0);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	/* 총알 Render */
	for (auto bullet : m_vecBullet)
	{
		bullet->Render();
	}
}
