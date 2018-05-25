#include "stdafx.h"
#include "Bullet.h"
#include "IScene.h"
#include "Collider.h"

Bullet::Bullet(GUN_TAG  bulletFor, float scale, float velocity)
	: Item(ITEM_TAG::Bullet, "Bullet", "I am a Bullet")
	, m_bulletFor(bulletFor)
	, m_scale(scale)       //0.08f
	, m_velocity(velocity) //10.f
	, m_isFire(false)      //아직 발사되지 않았다
	, m_pBulletMesh(nullptr)
	, m_isDie(false)
    , m_pBoxCollider(nullptr)
{
    switch (bulletFor)
    {
    case GUN_TAG::Pistol:
        {
            m_name = "Bullet (Pistol)";
        }
        break;
    case GUN_TAG::Rifle:
        {
            m_name = "Bullet (Rifle)";
        }
        break;
    }
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
	const float deltaTime = g_pTimeManager->GetDeltaTime(); //프레임당 초단위 시간간격

	if (m_isFire)
	{
        if (!m_pBoxCollider)
        {
            m_pBoxCollider = SetComponent<BoxCollider>();
            m_pBoxCollider->Init(D3DXVECTOR3(-0.2f, -0.2f, -0.4f), D3DXVECTOR3(0.2f, 0.2f, 0.4f));
            m_pBoxCollider->Move(GetPosition());
            m_pBoxCollider->SetTag(CollisionTag::kBullet);
        }

		m_pos.z += deltaTime * m_velocity; //이동거리 = 속력 * 경과시간, 즉 기존의 위치에 이동거리를 더해주어 앞으로 나아가게한다

        D3DXMATRIXA16 m;
        D3DXMatrixTranslation(&m, 0.0f, 0.0f, deltaTime * m_velocity);
        m_pBoxCollider->Update(m);

		if (IsInBorderArea()) //경계구역 안이면 총알 이동
			D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
		else                  //경계구역 밖이면 총알 죽임
			g_pCurrentScene->Destroy(this);

        //변환행렬
        m_matWorld = m_matS * m_matT;
	}
    else
    {
        Item::Update();
    }
}

void Bullet::Render()
{
	const auto dv = g_pDevice;
	//dv->SetRenderState(D3DRS_LIGHTING, false);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (m_isFire) //발사된 총알만 그려주기
	{
		dv->SetTransform(D3DTS_WORLD, &m_matWorld);
        dv->SetMaterial(&DXUtil::YELLOW_MTRL);
		m_pBulletMesh->DrawSubset(0);
	}
    else
    {
        Item::Render();
    }

	dv->SetRenderState(D3DRS_LIGHTING, true);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

bool Bullet::GetIsFire() const
{
    return m_isFire;
}

void Bullet::SetIsFire(const bool isFire)
{
    m_isFire = isFire;
}

float Bullet::GetVelocity() const
{
    return m_velocity;
}

bool Bullet::GetIsDie() const
{
    return m_isDie;
}

GUN_TAG Bullet::GetBulletFor()
{
    return m_bulletFor;
}

bool Bullet::IsBulletForThisGun(GUN_TAG gunTag)
{
	cout << "bulletFor: " << static_cast<int>(m_bulletFor) << ", " << "gunTag:" << static_cast<int>(gunTag) << endl;
	if (m_bulletFor == gunTag)
		return true;
	return false;
}

bool Bullet::IsInBorderArea()
{
	if (m_pos.z < 20.f) //현재는 Ground의 행이 20이므로
		return true;
	else
		m_isDie = true;
	return false;
}
