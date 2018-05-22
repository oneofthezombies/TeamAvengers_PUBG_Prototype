#include "stdafx.h"
#include "Bullet.h"
#include "IScene.h"

Bullet::Bullet(float scale, float velocity)
	: Item(ITEM_TAG::Bullet, "Bullet", "I am a Bullet")
	, m_scale(scale)       //0.08f
	, m_velocity(velocity) //10.f
	, m_isFire(false)      //아직 발사되지 않았다
	, m_pBulletMesh(nullptr)
	, m_isDie(false)
    , m_pBulletCollider(nullptr)
{
}

Bullet::~Bullet()
{
	SAFE_RELEASE(m_pBulletMesh);
    SAFE_RELEASE(m_pBulletCollider);
}

void Bullet::Init()
{
	D3DXCreateCylinder(g_pDevice, 2.f, 2.f, 10.f, 15, 10, &m_pBulletMesh, NULL); //메쉬 생성
	D3DXMatrixScaling(&m_matS, m_scale, m_scale, m_scale); //입력받은 매개변수로 크기 조정

    //VERTEX_PN* pV;
    //D3DXVECTOR3 min, max;
    //m_pBulletMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pV);
    //D3DXComputeBoundingBox((D3DXVECTOR3*)pV, m_pBulletMesh->GetNumVertices(), sizeof VERTEX_PN, &min, &max);
    //m_pBulletMesh->UnlockVertexBuffer();
}

void Bullet::Update()
{
	float deltaTime = g_pTimeManager->GetDeltaTime(); //프레임당 초단위 시간간격

	if (m_isFire)
	{
        if (!m_pBulletCollider)
        {
            m_pBulletCollider = new BulletCollider;
            m_pBulletCollider->Init(D3DXVECTOR3(-0.2f, -0.2f, -0.4f), D3DXVECTOR3(0.2f, 0.2f, 0.4f), GetPosition());
            m_pBulletCollider->bullet = this;
        }

		m_pos.z += deltaTime * m_velocity; //이동거리 = 속력 * 경과시간, 즉 기존의 위치에 이동거리를 더해주어 앞으로 나아가게한다

        D3DXMATRIXA16 m;
        D3DXMatrixTranslation(&m, 0.0f, 0.0f, deltaTime * m_velocity);
        m_pBulletCollider->Update(m);

		if (IsInBorderArea()) //경계구역 안이면 총알 이동
			D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
		else                  //경계구역 밖이면 총알 죽임
			g_pCurrentScene->Destroy(this);
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
	else
		m_isDie = true;
	return false;
}

void BulletCollider::Init(const D3DXVECTOR3& min, const D3DXVECTOR3& max, const D3DXVECTOR3& pos)
{
    bc = &SetCollider(min, max);

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, pos.x, pos.y, pos.z);
    bc->Update(m);
}

void BulletCollider::Update(const D3DXMATRIXA16& transform)
{
    bc->Update(transform);
}

void BulletCollider::OnCollision(ICollidable& other)
{
}
