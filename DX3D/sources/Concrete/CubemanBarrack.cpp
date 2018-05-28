#include "stdafx.h"
#include "CubemanBarrack.h"
#include "Cubeman.h"
#include "IScene.h"

CubemanBarrack::CubemanBarrack()
    : IDisplayObject()
{
}

CubemanBarrack::~CubemanBarrack()
{
}

void CubemanBarrack::Init()
{
    Cubeman* c1 = new Cubeman;
    c1->Init();
    c1->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
    c1->UpdatePositionYOnMap();
    g_pCurrentScene->AddSimpleDisplayObj(c1);
    m_cubemans.emplace(c1);

    Cubeman* c2 = new Cubeman;
    c2->Init();
    c2->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 40.0f));
    c2->UpdatePositionYOnMap();
    g_pCurrentScene->AddSimpleDisplayObj(c2);
    m_cubemans.emplace(c2);

    Cubeman* c3 = new Cubeman;
    c3->Init();
    c3->SetPosition(D3DXVECTOR3(40.0f, 0.0f, 10.0f));
    c3->UpdatePositionYOnMap();
    g_pCurrentScene->AddSimpleDisplayObj(c3);
    m_cubemans.emplace(c3);

    g_pObjectManager->AddToTagList(TAG_CUBEMAN_BARRACK, this);
}

void CubemanBarrack::Update()
{
}

void CubemanBarrack::Render()
{
}

int CubemanBarrack::GetNumCubemans()
{
    return m_cubemans.size();
}

void CubemanBarrack::RemoveCubeman(Cubeman& val)
{
    for (auto it = m_cubemans.begin(); it != m_cubemans.end(); ++it)
    {
        if (*it == &val)
        {
            g_pCurrentScene->Destroy(*it);
            m_cubemans.erase(it);
            break;
        }
    }
}
