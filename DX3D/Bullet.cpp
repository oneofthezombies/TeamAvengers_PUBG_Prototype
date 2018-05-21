#include "stdafx.h"
#include "Bullet.h"
#include "IScene.h"

Bullet::Bullet(float scale, float velocity)
	: m_scale(scale)       //0.08f
	, m_velocity(velocity) //10.f
	, m_isFire(false)      //아직 발사되지 않았다
	, m_pBulletMesh(nullptr)
{
}

Bullet::~Bullet()
{
	SAFE_RELEASE(m_pBulletMesh);
}

void Bullet::Init()
{
	D3DXCreateCylinder(g_pDevice, 2.f, 2.f, 10.f, 15, 10, &m_pBulletMesh, NULL); //메쉬 생성
	D3DXMatrixScaling(&m_matS, m_scale, m_scale, m_scale); //입력받은 매개변수로 크기 조정
}

void Bullet::Update()
{
	float deltaTime = g_pTimeManager->GetDeltaTime(); //프레임당 초단위 시간간격

	if (m_isFire)
	{
		m_pos.z += deltaTime * m_velocity; //이동거리 = 속력 * 경과시간, 즉 기존의 위치에 이동거리를 더해주어 앞으로 나아가게한다

		if (IsInBorderArea()) //경계구역 안이면 총알 이동
			D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
		else                  //경계구역을 넘어서면 총알을 죽임
			m_isFire = false;
	}

	//변환행렬
	m_matWorld = m_matS * m_matT;
}

void Bullet::Render()
{
	const auto dv = g_pDevice;
	dv->SetRenderState(D3DRS_LIGHTING, false);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (m_isFire) //발사된 총알만 그려주기
	{
		dv->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pBulletMesh->DrawSubset(0);
	}

	dv->SetRenderState(D3DRS_LIGHTING, true);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

bool Bullet::IsInBorderArea()
{
	if (m_pos.z < 20.f) //현재는 Ground의 행이 20이므로
		return true;
	return false;
}
