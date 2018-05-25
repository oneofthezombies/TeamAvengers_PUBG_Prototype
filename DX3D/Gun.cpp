#include "stdafx.h"
#include "Gun.h"
#include "Bullet.h"

Gun::Gun(GUN_TAG gunTag, bool canChangeBurstMode, int bulletNum, int bulletFireCoolTime, float velocity, float scale, float rotY)
	: Item(ITEM_TAG::Gun, "Gun", "I am a Gun")
	, m_gunTag(gunTag)
	, m_canChangeBurstMode(canChangeBurstMode)
	, m_maxBullet(bulletNum)
	, m_bulletFireCoolTime(bulletFireCoolTime) //0.4f
	, m_velocity(velocity) //5.f;
	, m_scale(scale)       //0.7f
	, m_rotY(rotY)         //-D3DXToRadian(90)
	, m_pGunMesh(nullptr)
{
    switch (gunTag)
    {
    case GUN_TAG::Pistol:
        {
            m_name = "Pistol";
            break;
        }
    case GUN_TAG::Rifle:
        {
            m_name = "Rifle";
            break;
        }
    }
}

Gun::~Gun()
{
	SAFE_RELEASE(m_pGunMesh);
}

void Gun::Init()
{
	//m_pos = D3DXVECTOR3(0.f, 4.f, -9 * 2.f);        //일단 하드코딩으로 위치 박음

	D3DXCreateTeapot(g_pDevice, &m_pGunMesh, NULL); //총 메쉬 생성 (임시로 주전자 모양)
	m_bulletFireCoolDown = m_bulletFireCoolTime;    //쿨다운을 쿨타임으로 초기화

	D3DXMatrixScaling(&m_matS, m_scale, m_scale, m_scale);
	D3DXMatrixRotationY(&m_matRotY, m_rotY);
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
}

void Gun::Update()
{
    Item::Update();

    if (m_state != ITEM_STATE::Dropped)
    {
        float deltaTime = g_pTimeManager->GetDeltaTime(); //프레임당 초단위 시간간격
        m_bulletFireCoolDown -= deltaTime;
        if (m_bulletFireCoolDown <= 0.f) m_bulletFireCoolDown = 0.f;

        D3DXMatrixRotationY(&m_matRotY, m_rotY);

        //변환행렬
        D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
        m_matWorld = m_matS * m_matRotY * m_matT;
    }
}

void Gun::Render()
{
	if (m_state == ITEM_STATE::InHand || m_state == ITEM_STATE::Equipped)
	{
		const auto dv = g_pDevice;
		dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        dv->SetRenderState(D3DRS_LIGHTING, true);
		dv->SetTransform(D3DTS_WORLD, &m_matWorld);
        
        if(m_gunTag == GUN_TAG::Pistol)
            dv->SetMaterial(&DXUtil::BLUE_MTRL);
        else if(m_gunTag == GUN_TAG::Rifle)
            dv->SetMaterial(&DXUtil::RED_MTRL);
        else
            dv->SetMaterial(&DXUtil::YELLOW_MTRL);

		m_pGunMesh->DrawSubset(0);

		dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
    else if (m_state == ITEM_STATE::Dropped)
    {
        Item::Render();
    }
}

void Gun::ShowBulletNumForDebug()
{
	Debug->EndLine();
	Debug->AddText("BulletNum: ");
	Debug->AddText(GetBulletNum());
	Debug->EndLine();
}

string Gun::GunTagToStrForDebug(GUN_TAG gunTag)
{
	switch (gunTag)
	{
	case GUN_TAG::Pistol:
		return "Pistol";
		break;
	case GUN_TAG::Rifle:
		return "Rifle";
		break;
	default:
		return "?";
		break;
	}
}

void Gun::Fire()
{
	if (m_bulletFireCoolDown <= 0.f)
	{
		m_bulletFireCoolDown = m_bulletFireCoolTime;

		if (m_vecPBullet.empty() == false)        //총알이 있으면
		{
            cout << "Bang Bnag~!" << endl;
			Bullet* bullet = m_vecPBullet.back(); //총알을 하나 꺼내고
			m_vecPBullet.pop_back();              //벡터에서 지워줌 (실제 릴리즈는 현재씬의 Update에서)
			bullet->SetIsFire(true);
			bullet->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z + 1.f));
			g_pCurrentScene->AddSimpleDisplayObj(bullet);
		}
	}
}

void Gun::Load(Bullet* bullet)
{	
	m_vecPBullet.emplace_back(bullet);
}

void Gun::SyncRot(float rotY)
{
    m_rotY = rotY - D3DXToRadian(90);
}
