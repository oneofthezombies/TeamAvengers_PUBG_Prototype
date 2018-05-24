#include "stdafx.h"
#include "Collider.h"

ColliderBase::ColliderBase(BaseObject& owner, const Type type)
    : ComponentBase(owner)
    , m_vCenter(0.0f, 0.0f, 0.0f)
    , m_type(type)
    , m_color(D3DCOLOR_XRGB(0, 255, 0))
    , m_pListner(nullptr)
{
    g_pCollisionManager->AddColliderBase(*this);
}

ColliderBase::~ColliderBase()
{
    g_pCollisionManager->RemoveColliderBase(*this);
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

D3DXVECTOR3 ColliderBase::GetCenter() const
{
    return m_vCenter;
}

void ColliderBase::SetListner(ICollisionListner& listner)
{
    m_pListner = &listner;
}

ICollisionListner* ColliderBase::GetListner() const
{
    return m_pListner;
}

SphereCollider::SphereCollider(BaseObject& owner)
    : ColliderBase(owner, ColliderBase::Type::kSphere)
{
}

void SphereCollider::Init(const float radius)
{
}

void SphereCollider::Update(const D3DXMATRIXA16& transform)
{
}

void SphereCollider::Render()
{
}

BoxCollider::BoxCollider(BaseObject& owner)
    : ColliderBase(owner, ColliderBase::Type::kBox)
    , m_vExtent(0.0f, 0.0f, 0.0f)
    , m_mTransform(0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Init(const D3DXVECTOR3& min, const D3DXVECTOR3& max)
{
    m_vCenter = (min + max) / 2.0f;
    m_vExtent = max - m_vCenter;
    D3DXMatrixIdentity(&m_mTransform);
}

void BoxCollider::Update(const D3DXMATRIXA16& transform)
{
    m_mTransform *= transform;
    D3DXVec3TransformCoord(&m_vCenter, &m_vCenter, &transform);
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
    dv->SetTexture(0, nullptr);
    dv->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, vertices.size(), indices.size() / 2, indices.data(), D3DFMT_INDEX16, vertices.data(), sizeof VERTEX_PC);
}

void BoxCollider::Move(const D3DXVECTOR3& val)
{
    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, val.x, val.y, val.z);
    Update(m);
}

D3DXVECTOR3 BoxCollider::GetExtent() const
{
    return m_vExtent;
}

const D3DXMATRIXA16& BoxCollider::GetTransform() const
{
    return m_mTransform;
}

ICollisionListner::ICollisionListner(BaseObject& owner)
    : ComponentBase(owner)
{
}

ICollisionListner::~ICollisionListner()
{
}
