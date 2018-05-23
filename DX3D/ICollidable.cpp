#include "stdafx.h"
#include "ICollidable.h"
#include "CollisionManager.h"
#include "Collider.h"

ICollidable::ICollidable()
    : IDisplayObject()
    , m_pCollider(nullptr)
{
    g_pCollisionManager->AddICollidable(*this);
}

ICollidable::~ICollidable()
{
    g_pCollisionManager->RemoveICollidable(*this);
    SAFE_DELETE(m_pCollider);
}

BoxCollider& ICollidable::SetCollider(const D3DXVECTOR3& min, const D3DXVECTOR3& max)
{
    if (m_pCollider)
        SAFE_DELETE(m_pCollider);

    m_pCollider = new BoxCollider;
    BoxCollider* ret = static_cast<BoxCollider*>(m_pCollider);
    ret->Init(min, max);
    return *ret;
}

SphereCollider& ICollidable::SetCollider(const float radius)
{
    if (m_pCollider)
        SAFE_DELETE(m_pCollider);

    m_pCollider = new SphereCollider;
    SphereCollider* ret = static_cast<SphereCollider*>(m_pCollider);
    ret->Init(radius);
    return *ret;
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
}
