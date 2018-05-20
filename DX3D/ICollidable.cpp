#include "stdafx.h"
#include "ICollidable.h"

ColliderBase::ColliderBase(Type type)
    : m_type(type)
{
}

void ColliderBase::Render()
{
}

ColliderBase::Type ColliderBase::GetType() const
{
    return m_type;
}

void ColliderBase::SetColor(const D3DCOLOR color)
{
    m_color = color;
}

SphereCollider::SphereCollider()
    : ColliderBase(ColliderBase::Type::Sphere)
{
}

BoxCollider::BoxCollider()
    : ColliderBase(ColliderBase::Type::Box)
    , m_vCenter(0.0f, 0.0f, 0.0f)
    , m_vExtent(0.0f, 0.0f, 0.0f)
    , m_mTransform(0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f)
{
}

void BoxCollider::Init(const D3DXVECTOR3& min, const D3DXVECTOR3& max)
{
    m_vCenter = (min + max) / 2.0f;
    m_vExtent = max - m_vCenter;
    D3DXMatrixIdentity(&m_mTransform);
}

void BoxCollider::Update(const D3DXMATRIXA16* transform)
{
    if (!transform) return;

    m_mTransform *= *transform;
    D3DXVec3TransformCoord(&m_vCenter, &m_vCenter, transform);
}

void BoxCollider::Render()
{
    vector<VERTEX_PC> vertices(8);
    vertices[0] = VERTEX_PC(D3DXVECTOR3(-m_vExtent.x, -m_vExtent.y, -m_vExtent.z), m_color);
    vertices[1] = VERTEX_PC(D3DXVECTOR3(-m_vExtent.x, m_vExtent.y, -m_vExtent.z), m_color);
    vertices[2] = VERTEX_PC(D3DXVECTOR3(m_vExtent.x, m_vExtent.y, -m_vExtent.z), m_color);
    vertices[3] = VERTEX_PC(D3DXVECTOR3(m_vExtent.x, -m_vExtent.y, -m_vExtent.z), m_color);
    vertices[4] = VERTEX_PC(D3DXVECTOR3(-m_vExtent.x, -m_vExtent.y, m_vExtent.z), m_color);
    vertices[5] = VERTEX_PC(D3DXVECTOR3(-m_vExtent.x, m_vExtent.y, m_vExtent.z), m_color);
    vertices[6] = VERTEX_PC(D3DXVECTOR3(m_vExtent.x, m_vExtent.y, m_vExtent.z), m_color);
    vertices[7] = VERTEX_PC(D3DXVECTOR3(m_vExtent.x, -m_vExtent.y, m_vExtent.z), m_color);
    
    vector<WORD> indices =
    {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7,
    };

    const auto dv = g_pDevice;
    dv->SetTransform(D3DTS_WORLD, &m_mTransform);
    dv->SetTexture(0, NULL);
    dv->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, vertices.size(), indices.size() / 2, indices.data(), D3DFMT_INDEX16, vertices.data(), sizeof VERTEX_PC);
}

D3DXVECTOR3 BoxCollider::GetCenter() const
{
    return m_vCenter;
}

D3DXVECTOR3 BoxCollider::GetExtent() const
{
    return m_vExtent;
}

const D3DXMATRIXA16& BoxCollider::GetTransform() const
{
    return m_mTransform;
}

ICollidable::ICollidable()
    : IDisplayObject()
    , m_pCollider(NULL)
{
}

ICollidable::~ICollidable()
{
    SAFE_DELETE(m_pCollider);
}

ColliderBase* ICollidable::GetCollider() const
{
    return m_pCollider;
}

void ICollidable::Init()
{
}

void ICollidable::Update()
{
}

void ICollidable::Render()
{
    SAFE_RENDER(m_pCollider);
}

void SampleCollidable::Init()
{
    BoxCollider* bc = new BoxCollider;
    bc->Init(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
    m_pCollider = bc;
}

void SampleCollidable::Update()
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    BoxCollider* bc = static_cast<BoxCollider*>(m_pCollider);
    D3DXMATRIXA16 tr;
    float trX = 0.0f;
    if (GetKeyState(VK_LEFT) & 0x8000)
    {
        trX -= 0.01f;
    }

    if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        trX += 0.01f;
    }

    D3DXMatrixTranslation(&tr, trX, 0.0f, 0.0f);
    bc->Update(&tr);
}

void SampleCollidable::OnCollision(ICollidable& other)
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));
}

void SampleCollidable2::Init()
{
    BoxCollider* bc = new BoxCollider;
    bc->Init(D3DXVECTOR3(-0.5f, -2.0f, -1.0f), D3DXVECTOR3(0.5f, 2.0f, 1.0f));
    m_pCollider = bc;
}

void SampleCollidable2::Update()
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    BoxCollider* bc = static_cast<BoxCollider*>(m_pCollider);
    D3DXMATRIXA16 tr;
    float rotY = 0.0f;
    float rotX = 0.0f;

    if (GetKeyState('W') & 0x8000)
    {
        rotX += 0.01f;
    }

    if (GetKeyState('S') & 0x8000)
    {
        rotX -= 0.01f;
    }

    if (GetKeyState('A') & 0x8000)
    {
        rotY -= 0.01f;
    }

    if (GetKeyState('D') & 0x8000)
    {
        rotY += 0.01f;
    }

    D3DXMatrixRotationYawPitchRoll(&tr, rotY, 0.0f, rotX);

    bc->Update(&tr);
}

void SampleCollidable2::OnCollision(ICollidable& other)
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));
}
