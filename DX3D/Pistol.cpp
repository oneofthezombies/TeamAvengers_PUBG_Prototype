#include "stdafx.h"
#include "Pistol.h"
#include "Bullet.h"
#include "IScene.h"

Pistol::Pistol(int bulletNum, int bulletFireCoolTime, float velocity, float scale, float rotY)
	: Item(ITEM_TAG::Pistol, "Pistol", "I am a Pistol")
	, m_maxBullet(bulletNum)
	, m_bulletFireCoolTime(bulletFireCoolTime) //0.4f
	, m_velocity(velocity) //5.f;
	, m_scale(scale)       //0.7f
	, m_rotY(rotY)         //-D3DXToRadian(90)
	, m_pGunMesh(nullptr)
{
}

Pistol::~Pistol()
{
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
}

void Pistol::Render()
{
	if (m_state == ITEM_STATE::Mounting)
	{
		const auto dv = g_pDevice;
		dv->SetRenderState(D3DRS_LIGHTING, false);
		dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		dv->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pGunMesh->DrawSubset(0);

		dv->SetRenderState(D3DRS_LIGHTING, true);
		dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

void Pistol::ShowBulletNumForDebug()
{
	Debug->EndLine();
	Debug->AddText("BulletNum: ");
	Debug->AddText(GetBulletNum());
	Debug->EndLine();
}

void Pistol::Fire()
{
	if (m_bulletFireCoolDown <= 0.f)
	{
		m_bulletFireCoolDown = m_bulletFireCoolTime;

		if (m_vecPBullet.empty() == false)        //총알이 있으면
		{
			Bullet* bullet = m_vecPBullet.back(); //총알을 하나 꺼내고
			m_vecPBullet.pop_back();              //벡터에서 지워줌 (실제 릴리즈는 현재씬의 Update에서)
			bullet->SetIsFire(true);
			bullet->SetPosition(&D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z + 1.f));
			g_pCurrentScene->AddSimpleDisplayObj(bullet);
		}
	}
}

void Pistol::Load(Bullet* bullet)
{	
	m_vecPBullet.emplace_back(bullet);
}
