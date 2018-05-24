#include "stdafx.h"
#include "IDisplayObject.h"

IDisplayObject::IDisplayObject()
    : BaseObject()
    , m_pParent(nullptr)
{
	D3DXMatrixIdentity(&m_matWorld);
}

IDisplayObject::~IDisplayObject()
{
}

void IDisplayObject::AddChild(IDisplayObject& val)
{
    val.m_pParent = this;
    m_vecPChild.push_back(&val);
}

D3DXVECTOR3 IDisplayObject::GetPosition() const
{
    return m_pos;
}

void IDisplayObject::SetPosition(const D3DXVECTOR3& pos)
{
    m_pos = pos;
}

D3DXVECTOR3 IDisplayObject::GetRotation() const
{
    return m_rot;
}

const D3DXMATRIXA16& IDisplayObject::GetWorldMatrix() const
{
    return m_matWorld;
}

void IDisplayObject::Release()
{
    ReleaseChildren();
    BaseObject::Release();
}

void IDisplayObject::UpdateChildren()
{
    for (auto& c : m_vecPChild)
        SAFE_UPDATE(c);
}

void IDisplayObject::RenderChildren()
{
    for (auto& c : m_vecPChild)
        SAFE_RENDER(c);
}

void IDisplayObject::ReleaseChildren()
{
    for (auto c : m_vecPChild)
        SAFE_RELEASE(c);
}
