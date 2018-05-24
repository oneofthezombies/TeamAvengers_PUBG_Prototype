#include "stdafx.h"
#include "SampleCollider.h"
#include "Collider.h"

SampleCollisionListner1::SampleCollisionListner1(BaseObject& owner)
    : ICollisionListner(owner)
{
}

SampleCollisionListner1::~SampleCollisionListner1()
{
}

void SampleCollisionListner1::OnCollisionEnter(const ColliderBase& other)
{
    static_cast<SampleColliderOwner1*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));

    cout << "SampleCollisionListner1::OnCollisionEnter()\n";
}

void SampleCollisionListner1::OnCollisionExit(const ColliderBase& other)
{
    static_cast<SampleColliderOwner1*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    cout << "SampleCollisionListner1::OnCollisionExit()\n";
}

void SampleCollisionListner1::OnCollisionStay(const ColliderBase& other)
{
    Debug->AddText("SampleCollisionListner1::OnCollisionStay()\n");
}

SampleColliderOwner1::SampleColliderOwner1()
    : m_pBoxCollider(nullptr)
    , m_pCollisionListner(nullptr)
{
}

SampleColliderOwner1::~SampleColliderOwner1()
{
}

void SampleColliderOwner1::Init()
{
    m_pCollisionListner = SetComponent<SampleCollisionListner1>();
    
    m_pBoxCollider = SetComponent<BoxCollider>();
    m_pBoxCollider->SetListner(*m_pCollisionListner);
    m_pBoxCollider->Init(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, 7.0f, 0.0f, 0.0f);
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

    Debug->AddText("! ");
    Debug->AddText(m_pos);
    Debug->EndLine();
}

void SampleColliderOwner1::Render()
{
}

SampleCollisionListner2::SampleCollisionListner2(BaseObject& owner)
    : ICollisionListner(owner)
{
}

SampleCollisionListner2::~SampleCollisionListner2()
{
}

void SampleCollisionListner2::OnCollisionEnter(const ColliderBase& other)
{
    static_cast<SampleColliderOwner2*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));

    cout << "SampleCollisionListner2::OnCollisionEnter()\n";
}

void SampleCollisionListner2::OnCollisionExit(const ColliderBase& other)
{
    static_cast<SampleColliderOwner2*>(GetOwner())->m_pBoxCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    cout << "SampleCollisionListner2::OnCollisionExit()\n";
}

void SampleCollisionListner2::OnCollisionStay(const ColliderBase& other)
{
    Debug->AddText("SampleCollisionListner2::OnCollisionStay()\n");
}

SampleColliderOwner2::SampleColliderOwner2()
    : m_pBoxCollider(nullptr)
    , m_pCollisionListner(nullptr)
{
}

SampleColliderOwner2::~SampleColliderOwner2()
{
}

void SampleColliderOwner2::Init()
{
    m_pCollisionListner = SetComponent<SampleCollisionListner2>();

    m_pBoxCollider = SetComponent<BoxCollider>();
    m_pBoxCollider->SetListner(*m_pCollisionListner);
    m_pBoxCollider->Init(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, 7.0f, 0.0f, 2.0f);
    m_pBoxCollider->Update(m);
}

void SampleColliderOwner2::Update()
{
}

void SampleColliderOwner2::Render()
{
}
