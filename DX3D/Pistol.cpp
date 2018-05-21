#include "stdafx.h"
#include "Pistol.h"
#include "Bullet.h"
#include "IScene.h"

Pistol::Pistol(int bulletNum, int bulletFireCoolTime, float velocity, float scale, float rotY)
	: m_bulletNum(bulletNum)
	, m_bulletFireCoolTime(bulletFireCoolTime) //0.4f
	, m_velocity(velocity) //5.f;
	, m_scale(scale)       //0.7f
	, m_rotY(rotY)         //-D3DXToRadian(90)
	, m_pGunMesh(nullptr)
{
}

Pistol::~Pistol()
{
	/* 총알 Release */
	for (auto bullet : m_vecBullet)
	{
		SAFE_RELEASE(bullet);
	}

	SAFE_RELEASE(m_pGunMesh);
}

void Pistol::Init()
{
	m_pos = D3DXVECTOR3(0.f, 4.f, -9 * 2.f);        //일단 하드코딩으로 위치 박음

	D3DXCreateTeapot(g_pDevice, &m_pGunMesh, NULL); //총 메쉬 생성 (임시로 주전자 모양)
	m_bulletFireCoolDown = m_bulletFireCoolTime;    //쿨다운을 쿨타임으로 초기화

	D3DXMatrixScaling(&m_matS, m_scale, m_scale, m_scale);
	D3DXMatrixRotationY(&m_matRotY, m_rotY);
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);

	//최대 장전 개수에서 현재 있는 총알 개수를 빼준만큼 장전해준다
	for (int i = 0; i < m_bulletNum; ++i)
	{
		Bullet* bullet = new Bullet(0.08f, 10.f);
		bullet->Init(); /* 총알 Init */
		m_vecBullet.emplace_back(bullet);
	}
}

void Pistol::Update()
{
	float deltaTime = g_pTimeManager->GetDeltaTime(); //프레임당 초단위 시간간격

	//총알 발사 쿨타임
	m_bulletFireCoolDown -= deltaTime;
	if (m_bulletFireCoolDown <= 0.f) m_bulletFireCoolDown = 0.f;

	//변환행렬
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = m_matS * m_matRotY * m_matT;

	/* 총알 Update */
	for (auto bullet : m_vecBullet)
	{
		SAFE_UPDATE(bullet);
	}
}

void Pistol::Render()
{
	const auto dv = g_pDevice;
	dv->SetRenderState(D3DRS_LIGHTING, false);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	dv->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGunMesh->DrawSubset(0);

	dv->SetRenderState(D3DRS_LIGHTING, true);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	/* 총알 Render */
	for (auto bullet : m_vecBullet)
	{
		SAFE_RENDER(bullet);
	}

	Debug->AddText("The number of Bullets: ");
	Debug->AddText(m_vecBullet.size());
	Debug->EndLine();
}

void Pistol::Fire()
{
	if (m_bulletFireCoolDown <= 0.f)
	{
		m_bulletFireCoolDown = m_bulletFireCoolTime;

		for (auto bullet : m_vecBullet)
		{
			if (bullet->GetIsFire() == false) //소멸된 미사일 중에서 하나를 살린다
			{
				bullet->SetIsFire(true);
				bullet->SetPosition(&D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z + 1.f)); //플레이어 위치에서 발사하되, 플레이어보다 약간 앞쪽에서 발사
				break; //미사일 하나만 날리고 반복문 탈출
			}
		}
	}
}

void Pistol::Load()
{	
}
