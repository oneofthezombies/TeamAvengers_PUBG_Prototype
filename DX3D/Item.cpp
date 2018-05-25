#include "stdafx.h"
#include "Item.h"
#include "Collider.h"

Item::Item(ITEM_TAG tag, string name, string desc)
    : IDisplayObject()
	, m_tag(tag)
	, m_name(name)
	, m_desc(desc)
	, m_state(ITEM_STATE::Dropped)
    , m_pBoxCollider(nullptr)
    , m_pMesh(nullptr)
{
}

Item::~Item()
{
    SAFE_RELEASE(m_pMesh);
}

void Item::Init()
{
}

void Item::Update()
{
    if (m_state == ITEM_STATE::Dropped)
    {
        if (!m_pBoxCollider)
        {
            m_pBoxCollider = SetComponent<BoxCollider>();
            m_pBoxCollider->Init(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
            m_pBoxCollider->Move(m_pos);
            m_pBoxCollider->SetTag(CollisionTag::kItem);

            D3DXCreateBox(g_pDevice, 0.9f, 0.9f, 0.9f, &m_pMesh, nullptr);      
        }
    }
    else
    {
        if (m_pBoxCollider)
        {
            RemoveComponent<BoxCollider>();
            m_pBoxCollider = nullptr;

            SAFE_RELEASE(m_pMesh);
        }
    }

    UpdateTransform();
}

void Item::Render()
{
    if (!IsVisible()) return;

    if (m_pMesh)
    {
        const auto dv = g_pDevice;
        dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        dv->SetRenderState(D3DRS_LIGHTING, true);
        dv->SetTransform(D3DTS_WORLD, &m_matWorld);
        dv->SetMaterial(&GetMaterialByItemTag());
        dv->SetTexture(0, nullptr);
        m_pMesh->DrawSubset(0);
    }
}

const string& Item::GetName() const
{
    return m_name;
}

const D3DMATERIAL9& Item::GetMaterialByItemTag()
{
    switch (m_tag)
    {
    case ITEM_TAG::Bullet:
        return DXUtil::YELLOW_MTRL;

    case ITEM_TAG::Gun:
        return DXUtil::RED_MTRL;

    default:
        return DXUtil::WHITE_MTRL;
    }
}

bool Item::IsVisible()
{
    switch (m_state)
    {
    case ITEM_STATE::Dropped:
    case ITEM_STATE::Equipped:
    case ITEM_STATE::Held:
        return true;
    default:
        return false;
    }
}
