#include "stdafx.h"
#include "SceneShotting.h"
#include "Ground.h"
#include "PlayerAni.h"
#include "Gun.h"
#include "Bullet.h"
#include "SkyBox.h"
#include "UIButton.h"
#include "UIGameOver.h"
#include "SampleUIButtonListener.h"
#include "UIManager.h"
#include "UIInteractionMessage.h"
#include "Cubeman.h"
#include "SampleCollider.h"

SceneShotting::SceneShotting()
	: m_pGround(nullptr)
	, m_pPlayerAni(nullptr)
    , m_pPistol(nullptr)
	, m_pRifle(nullptr)
    , m_pSampleUIButtonListener(nullptr)
{
}

SceneShotting::~SceneShotting()
{
	OnDestructIScene();
}

void SceneShotting::Init()
{
    InitSkyBox();
    InitLight();

    //x, y, z ±âÁØ¼±
    InitAxises();

	//¹Ù´Ú
    InitGroundGrid();

	//ÇÃ·¹ÀÌ¾î
    InitPlayer();

	//±ÇÃÑ
	m_pPistol = new Gun(GUN_TAG::Pistol, false, 10, 0.4f, 5.f, 0.7f, -D3DXToRadian(90));
	m_pPistol->Init();
    m_pPistol->SetPosition(D3DXVECTOR3(2.0f, 0.0f, 15.0f));
	AddSimpleDisplayObj(m_pPistol);

	//¼ÒÃÑ
	m_pRifle = new Gun(GUN_TAG::Rifle, true, 10, 10.f, 5.f, 1.5f, -D3DXToRadian(90));
	m_pRifle->Init();
    m_pRifle->SetPosition(D3DXVECTOR3(3.0f, 0.0f, 15.0f));
	AddSimpleDisplayObj(m_pRifle);

	//±ÇÃÑ¿ë ÃÑ¾Ë 5°³ »ý¼º
	m_vecPBulletForPistol.reserve(5);
	for (int i = 0; i < 5; ++i)
	{
		Bullet* bullet = new Bullet(GUN_TAG::Pistol, 0.08f, 10.f);
		bullet->Init();
        bullet->SetPosition(D3DXVECTOR3(2.0f, 0.0f, 2.0f + static_cast<float>(i)));
		m_vecPBulletForPistol.push_back(bullet);
		AddSimpleDisplayObj(bullet);
	}
	//¼ÒÃÑ¿ë ÃÑ¾Ë 5°³ »ý¼º
	m_vecPBulletForRifle.reserve(5);
	for (int i = 0; i < 5; ++i)
	{
		Bullet* bullet = new Bullet(GUN_TAG::Rifle, 0.05f, 15.f);
		bullet->Init();
        bullet->SetPosition(D3DXVECTOR3(3.0f, 0.0f, 2.0f + static_cast<float>(i)));
		m_vecPBulletForRifle.push_back(bullet);
		AddSimpleDisplayObj(bullet);
	}

    Cubeman* cm = new Cubeman;
    cm->Init();
    cm->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 20.0f));
    AddSimpleDisplayObj(cm);

    //InitSamples();

    g_pCollisionManager->SubscribeCollisionEvent(CollisionTag::kFoo, CollisionTag::kBar);
    g_pCollisionManager->SubscribeCollisionEvent(CollisionTag::kBullet, CollisionTag::kEnemy);
}

void SceneShotting::Update()
{
	OnUpdateIScene();

    if (g_pKeyManager->IsOnceKeyDown('0'))
    {
        Cubeman* cm = new Cubeman;
        cm->Init();
        cm->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 20.0f));
        AddSimpleDisplayObj(cm);
    }
}

void SceneShotting::Render()
{
	OnRenderIScene();

	//x, y, z ±âÁØ¼± ±×¸®±â 
    RenderAxises();
}

void SceneShotting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void SceneShotting::InitSkyBox()
{
    SkyBox* skyBox = new SkyBox;
    D3DXMATRIXA16 m;
    const float scale = 100.0f;
    D3DXMatrixScaling(&m, scale, scale, scale);
    skyBox->Init(m);
    AddSimpleDisplayObj(skyBox);
}

void SceneShotting::InitLight()
{
    D3DLIGHT9 light = DXUtil::InitDirectional(&D3DXVECTOR3(1.0f, -1.0f, 1.0f), &WHITE);
    const auto dv = g_pDevice;
    dv->SetLight(0, &light);
    dv->LightEnable(0, true);
}

void SceneShotting::InitAxises()
{
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
}

void SceneShotting::InitGroundGrid()
{
    m_pGround = new Ground(6, 20, 2.f);
    m_pGround->Init();
    AddSimpleDisplayObj(m_pGround);
}

void SceneShotting::InitPlayer()
{
    m_pPlayerAni = new PlayerAni;
    m_pPlayerAni->Init();
    AddSimpleDisplayObj(m_pPlayerAni);
}

void SceneShotting::InitSamples()
{
    UIButton* sampleUIB = new UIButton;
    sampleUIB->Init();
    sampleUIB->SetSize(D3DXVECTOR2(200.0f, 200.0f));
    sampleUIB->SetText(g_pFontManager->GetFont(Font::kIdle), TEXT("Sample"));
    m_pSampleUIButtonListener = new SampleUIButtonListener;
    m_pSampleUIButtonListener->SetUIButton(*sampleUIB);
    g_pUIManager->RegisterUIObject(*sampleUIB);

    SampleColliderOwner1* sco1 = new SampleColliderOwner1;
    sco1->Init();
    AddSimpleDisplayObj(sco1);

    SampleColliderOwner2* sco2 = new SampleColliderOwner2;
    sco2->Init();
    AddSimpleDisplayObj(sco2);
}

void SceneShotting::RenderAxises()
{
    D3DXMATRIXA16 matI;
    D3DXMatrixIdentity(&matI);

    const auto dv = g_pDevice;
    dv->SetRenderState(D3DRS_LIGHTING, false);

    dv->SetTransform(D3DTS_WORLD, &matI);
    dv->SetFVF(VERTEX_PC::FVF);
    dv->DrawPrimitiveUP(D3DPT_LINELIST, m_vecBaseline.size() / 2, &m_vecBaseline[0], sizeof(VERTEX_PC));

    dv->SetRenderState(D3DRS_LIGHTING, true);
}

void SceneShotting::RemoveItemPointer(Item& val)
{
    if (m_pPistol == &val)
    {
        m_pPistol = nullptr;
        return;
    }

    if (m_pRifle == &val)
    {
        m_pRifle = nullptr;
        return;
    }

    for (auto it = m_vecPBulletForRifle.begin(); it != m_vecPBulletForRifle.end(); ++it)
    {
        if (*it == &val)
        {
            m_vecPBulletForRifle.erase(it);
            return;
        }
    }

    for (auto it = m_vecPBulletForPistol.begin(); it != m_vecPBulletForPistol.end(); ++it)
    {
        if (*it == &val)
        {
            m_vecPBulletForPistol.erase(it);
            return;
        }
    }
}
