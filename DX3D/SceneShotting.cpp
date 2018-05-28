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
#include "HeightMap.h"
#include "CubemanBarrack.h"
#include "SkinnedMesh.h"

SceneShotting::SceneShotting()
    : m_pHeightMap(nullptr)
	, m_pGround(nullptr)
	, m_pPlayerAni(nullptr)
    , m_pPistol(nullptr)
	, m_pRifle(nullptr)
    , m_pSampleUIButtonListener(nullptr)
{
}

SceneShotting::~SceneShotting()
{
	OnDestructIScene();

    SAFE_RELEASE(m_cubemanBarrack);
}

void SceneShotting::Init()
{
    InitSkyBox();
    InitLight();
    InitHeightMap();

    //x, y, z 기준선
    //InitAxises();

	//바닥
    //InitGroundGrid();

	//플레이어
    InitPlayer();

	//권총
	m_pPistol = new Gun(GUN_TAG::Pistol, false, 10, 0.4f, 5.f, 0.7f, -D3DXToRadian(90));
	m_pPistol->Init();
    m_pPistol->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 20.0f));
    m_pPistol->SetHeightOffset(0.5f);
    m_pPistol->UpdatePositionYOnMap();
	AddSimpleDisplayObj(m_pPistol);

	//소총
	m_pRifle = new Gun(GUN_TAG::Rifle, true, 10, 10.f, 5.f, 0.9f, -D3DXToRadian(90));
	m_pRifle->Init();
    m_pRifle->SetPosition(D3DXVECTOR3(15.0f, 0.0f, 15.0f));
    m_pRifle->SetHeightOffset(0.5f);
    m_pRifle->UpdatePositionYOnMap();
	AddSimpleDisplayObj(m_pRifle);

	//권총용 총알 5개 생성
	m_vecPBulletForPistol.reserve(5);
	for (int i = 0; i < 5; ++i)
	{
		Bullet* bullet = new Bullet(GUN_TAG::Pistol, 0.08f, 10.f);
		bullet->Init();
        bullet->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 21.0f + static_cast<float>(i)));
        bullet->SetHeightOffset(0.5f);
        bullet->UpdatePositionYOnMap();
		m_vecPBulletForPistol.push_back(bullet);
		AddSimpleDisplayObj(bullet);
	}
	//소총용 총알 5개 생성
	m_vecPBulletForRifle.reserve(5);
	for (int i = 0; i < 5; ++i)
	{
		Bullet* bullet = new Bullet(GUN_TAG::Rifle, 0.05f, 15.f);
		bullet->Init();
        bullet->SetPosition(D3DXVECTOR3(15.0f, 0.0f, 16.0f + static_cast<float>(i)));
        bullet->SetHeightOffset(0.5f);
        bullet->UpdatePositionYOnMap();
		m_vecPBulletForRifle.push_back(bullet);
		AddSimpleDisplayObj(bullet);
	}

    m_cubemanBarrack = new CubemanBarrack;
    m_cubemanBarrack->Init();

    //InitSamples();

    ////잠시 ray를 test 하기 위한 vertex //JH
    //float factor = 15.0f;
    //vector<D3DXVECTOR3> wallArr;
    //wallArr.resize(18);
    ////정면
    //wallArr[0]=D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    //wallArr[1]=D3DXVECTOR3(0.0f, factor, 0.0f);
    //wallArr[2]=D3DXVECTOR3(factor, 0.0f, 0.0f);
    //wallArr[3]=D3DXVECTOR3(factor, 0.0f, 0.0f);
    //wallArr[4]=D3DXVECTOR3(0.0f, factor, 0.0f);
    //wallArr[5]=D3DXVECTOR3(factor, factor, 0.0f);
    ////오른쪽 편
    //wallArr[6] = D3DXVECTOR3(factor, 0.0f, 0.0f);
    //wallArr[7] = D3DXVECTOR3(factor, factor, 0.0f);
    //wallArr[8] = D3DXVECTOR3(factor, 0.0f, -factor);
    //wallArr[9] = D3DXVECTOR3(factor, 0.0f, -factor);
    //wallArr[10] = D3DXVECTOR3(factor, factor, 0.0f);
    //wallArr[11] = D3DXVECTOR3(factor, factor, -factor);
    ////위 편
    //wallArr[12] = D3DXVECTOR3(0.0f, factor, 0.0f);
    //wallArr[13] = D3DXVECTOR3(0.0f, factor, -factor);
    //wallArr[14] = D3DXVECTOR3(factor, factor, 0.0f);
    //wallArr[15] = D3DXVECTOR3(factor, factor, 0.0f);
    //wallArr[16] = D3DXVECTOR3(0.0f, factor, -factor);
    //wallArr[17] = D3DXVECTOR3(factor, factor, -factor);

    //D3DXMATRIXA16 matT;
    //D3DXMatrixTranslation(&matT, 10.0f, 0.0f, 10.0f);
    //for (int i = 0; i < 18; i++)
    //{
    //    D3DXVec3TransformCoord(&wallArr[i], &wallArr[i], &matT);
    //    vecVertex_sample.push_back(VERTEX_PC(wallArr[i], D3DCOLOR_XRGB(0, 0, 255)));
    //}
    //g_pCameraManager->SetWall(wallArr);
    ////---------------

    //SkinnedMesh* m_skinnedMesh = new SkinnedMesh;
    //m_skinnedMesh->Init();
    //AddSimpleDisplayObj(m_skinnedMesh);

    g_pCollisionManager->SubscribeCollisionEvent(CollisionTag::kFoo, CollisionTag::kBar);
    g_pCollisionManager->SubscribeCollisionEvent(CollisionTag::kBullet, CollisionTag::kEnemy);
    g_pCollisionManager->SubscribeCollisionEvent(CollisionTag::kEnemy, CollisionTag::kPlayer);
}

void SceneShotting::Update()
{
    g_pSoundManager->Stop(static_cast<int>(SOUND_TAG::Lobby));
    g_pSoundManager->RepeatPlay(static_cast<int>(SOUND_TAG::Background), SOUND_TAG::Background);

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

	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);

	const auto dv = g_pDevice;
	dv->SetRenderState(D3DRS_LIGHTING, false);
	
	dv->SetTransform(D3DTS_WORLD, &matI);
	dv->SetFVF(VERTEX_PC::FVF);

	//dv->DrawPrimitiveUP(D3DPT_LINELIST, m_vecBaseline.size() / 2, &m_vecBaseline[0], sizeof(VERTEX_PC));
    
    ////잠시 ray를 test 하기 위한 vertex //JH
    //dv->DrawPrimitiveUP(D3DPT_TRIANGLELIST, vecVertex_sample.size() / 3, &vecVertex_sample[0], sizeof(VERTEX_PC));
	
    dv->SetRenderState(D3DRS_LIGHTING, true);

    //RenderAxises();
}

void SceneShotting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void SceneShotting::InitSkyBox()
{
    SkyBox* skyBox = new SkyBox;
    D3DXMATRIXA16 s, t, m;
    const float scale = 100.0f;
    D3DXMatrixScaling(&s, scale, scale, scale);
    D3DXMatrixTranslation(&t, 50.0f, 10.0f, 50.0f);
    m = s * t;
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

void SceneShotting::InitHeightMap()
{
    D3DXMATRIXA16 s;
    D3DXMatrixScaling(&s, 0.4f, 0.03f, 0.4f);
    m_pHeightMap = new HeightMap; 
    AddSimpleDisplayObj(m_pHeightMap);
    m_pHeightMap->SetDimension(257);
    m_pHeightMap->Load("resources/heightmap/HeightMap.raw", &s);
    m_pHeightMap->Init();
    D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;
    m_pHeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture(string("resources/heightmap/terrain3.jpg")));

    g_pMapManager->AddMap("heightmap", m_pHeightMap);
    g_pMapManager->SetCurrentMap("heightmap");
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
    m_pPlayerAni->UpdatePositionYOnMap();
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
