#include "stdafx.h"
#include "SampleCollider.h"
#include "Collider.h"

SampleCollisionListener1::SampleCollisionListener1(BaseObject& owner)
    : ICollisionListener(owner)
{
}

SampleCollisionListener1::~SampleCollisionListener1()
{
}

void SampleCollisionListener1::OnCollisionEnter(const ColliderBase& other)
{
    static_cast<SampleColliderOwner1*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));

    cout << "SampleCollisionListener1::OnCollisionEnter()\n";
}

void SampleCollisionListener1::OnCollisionExit(const ColliderBase& other)
{
    static_cast<SampleColliderOwner1*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    cout << "SampleCollisionListener1::OnCollisionExit()\n";
}

void SampleCollisionListener1::OnCollisionStay(const ColliderBase& other)
{
    Debug->AddText("SampleCollisionListener1::OnCollisionStay()\n");
}

SampleColliderOwner1::SampleColliderOwner1()
    : m_pBoxCollider(nullptr)
    , m_pCollisionListener(nullptr)
{
}

SampleColliderOwner1::~SampleColliderOwner1()
{
}

void SampleColliderOwner1::Init()
{
    m_pCollisionListener = SetComponent<SampleCollisionListener1>();
    
    m_pBoxCollider = SetComponent<BoxCollider>();
    m_pBoxCollider->SetListener(*m_pCollisionListener);
    m_pBoxCollider->Init(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
    m_pBoxCollider->SetTag(CollisionTag::kFoo);

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, 7.0f, 0.0f, 5.0f);
    m_pBoxCollider->Update(m);
}

void SampleColliderOwner1::Update()
{
    float trZ = 0.0f;
    if (GetKeyState('O') & 0x8000)
        trZ += 0.1f;

    if (GetKeyState('P') & 0x8000)
        trZ -= 0.1f;

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, 0.0f, 0.0f, trZ);
    m_pBoxCollider->Update(m);

    Debug->AddText("SampleColliderOwner move key : 'O', 'P'\n");
}

void SampleColliderOwner1::Render()
{
}

SampleCollisionListener2::SampleCollisionListener2(BaseObject& owner)
    : ICollisionListener(owner)
{
}

SampleCollisionListener2::~SampleCollisionListener2()
{
}

void SampleCollisionListener2::OnCollisionEnter(const ColliderBase& other)
{
    static_cast<SampleColliderOwner2*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));

    cout << "SampleCollisionListener2::OnCollisionEnter()\n";
}

void SampleCollisionListener2::OnCollisionExit(const ColliderBase& other)
{
    static_cast<SampleColliderOwner2*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    cout << "SampleCollisionListener2::OnCollisionExit()\n";
}

void SampleCollisionListener2::OnCollisionStay(const ColliderBase& other)
{
    Debug->AddText("SampleCollisionListener2::OnCollisionStay()\n");
}

SampleColliderOwner2::SampleColliderOwner2()
    : m_pBoxCollider(nullptr)
    , m_pCollisionListener(nullptr)
{
}

SampleColliderOwner2::~SampleColliderOwner2()
{
}

void SampleColliderOwner2::Init()
{
    m_pCollisionListener = SetComponent<SampleCollisionListener2>();

    m_pBoxCollider = SetComponent<BoxCollider>();
    m_pBoxCollider->SetListener(*m_pCollisionListener);
    m_pBoxCollider->Init(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
    m_pBoxCollider->SetTag(CollisionTag::kBar);

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, 7.0f, 0.0f, 7.0f);
    m_pBoxCollider->Update(m);
}

void SampleColliderOwner2::Update()
{
}

void SampleColliderOwner2::Render()
{
}
