#include "stdafx.h"
#include "SampleCollidable.h"
#include "UIInteractionMessage.h"
#include "UIManager.h"
#include "IScene.h"
#include "Collider.h"

CollidablePlayerBox::CollidablePlayerBox()
    : ICollidable()
    , bc(nullptr)
{
}

void CollidablePlayerBox::Init()
{
    bc = &SetCollider(D3DXVECTOR3(-1.5f, -3.5f, -1.5f), D3DXVECTOR3(1.5f, 3.5f, 1.5f));

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, 0.0f, 3.0f, -20.0f);
    bc->Update(m);
}

void CollidablePlayerBox::Update()
{
    const float dt = g_pTimeManager->GetDeltaTime();

    bc->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    D3DXMATRIXA16 m;
    float trZ = 0.0f;
    float trX = 0.0f;
    const float vel = 5.0f;
    const float dist = vel * dt;
    if (GetKeyState('W') & 0x8000)
        trZ += dist;

    if (GetKeyState('S') & 0x8000)
        trZ -= dist;

    if (GetKeyState('A') & 0x8000)
        trX -= dist;

    if (GetKeyState('D') & 0x8000)
        trX += dist;

    D3DXMatrixTranslation(&m, trX, 0.0f, trZ);
    bc->Update(m);
}

void CollidablePlayerBox::OnCollision(ICollidable& other)
{
    bc->SetColor(D3DCOLOR_XRGB(255, 0, 0));
}

CollidableItemBox::CollidableItemBox()
    : ICollidable()
    , bc(nullptr)
    , uiim(nullptr)
{
}

void CollidableItemBox::Init()
{
    bc = &SetCollider(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));

    D3DXMATRIXA16 m;
    D3DXMatrixRotationYawPitchRoll(&m, D3DX_PI * 0.25f, 0.0f, 0.0f);
    bc->Update(m);
    D3DXMatrixTranslation(&m, 3.0f, 0.5f, 0.0f);
    bc->Update(m);

    uiim = new UIInteractionMessage;
    uiim->Init();
    const float max = numeric_limits<float>::max();
    uiim->SetPosition(D3DXVECTOR3(max, max, 0.0f));
    g_pUIManager->RegisterUIObject(*uiim);
}

void CollidableItemBox::Update()
{
    bc->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    const float max = numeric_limits<float>::max();
    uiim->SetPosition(D3DXVECTOR3(max, max, 0.0f));
}

void CollidableItemBox::OnCollision(ICollidable& other)
{
    bc->SetColor(D3DCOLOR_XRGB(255, 0, 0));

    D3DVIEWPORT9 vp;
    g_pDevice->GetViewport(&vp);
    D3DXMATRIXA16 proj, view;
    g_pDevice->GetTransform(D3DTS_PROJECTION, &proj);
    g_pDevice->GetTransform(D3DTS_VIEW, &view);
    D3DXVECTOR3 v;
    D3DXVec3Project(&v, &GetCollider()->GetCenter(), &vp, &proj, &view, nullptr);
    uiim->SetPosition(v);

    if (GetAsyncKeyState('F') & 0x0001)
    {
        g_pCurrentScene->Destroy(this);
    }
}
