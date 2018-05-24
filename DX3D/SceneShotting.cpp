#include "stdafx.h"
#include "SceneShotting.h"
#include "Ground.h"
//#include "PlayerTemp.h"
#include "PlayerAni.h"
#include "Pistol.h"
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
	//, m_pPlayerAniTemp(nullptr)
	, m_pPlayerAni(nullptr)
    , m_pPistol(nullptr)
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

    //x, y, z 기준선
    InitAxises();

	//바닥
    InitGroundGrid();

    InitPlayer();

	//권총
	m_pPistol = new Pistol(10, 0.4f, 5.f, 0.7f, -D3DXToRadian(90));
	m_pPistol->Init();
    m_pPistol->SetPosition(D3DXVECTOR3(2.0f, 0.0f, 15.0f));
	AddSimpleDisplayObj(m_pPistol);

	//총알 10개 생성
	m_vecPBullet.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		Bullet* bullet = new Bullet(0.08f, 10.f);
		bullet->Init();
        bullet->SetPosition(D3DXVECTOR3(2.0f, 0.0f, 2.0f + static_cast<float>(i)));
		m_vecPBullet.push_back(bullet);
		AddSimpleDisplayObj(bullet);
	}

	////총이랑 총알먹기 //포인터에 대한 소유권을 명확히 해야한다
	//m_pPlayerAni->PutItemInInventory(m_pPistol);
	//m_pPistol = nullptr;
	//for (auto bullet : m_vecPBullet)
	//{ 
	//	m_pPlayerAni->PutItemInInventory(bullet);
	//}
	//m_vecPBullet.clear();

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

	//x, y, z 기준선 그리기 
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

    for (auto it = m_vecPBullet.begin(); it != m_vecPBullet.end(); ++it)
    {
        if (*it == &val)
        {
            m_vecPBullet.erase(it);
            return;
        }
    }
}
