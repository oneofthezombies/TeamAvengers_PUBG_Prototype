#include "stdafx.h"
#include "IDisplayObject.h"


IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
}

IDisplayObject::~IDisplayObject()
{
}

void IDisplayObject::AddChild(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild.push_back(pChild);
	pChild->m_pParent = this;
}

void IDisplayObject::ReleaseAll()
{
	for (auto child : m_vecPChild)
		if (child) child->ReleaseAll();

	Release();
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
