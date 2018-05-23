#include "stdafx.h"
#include "ICollisionListner.h"
#include "BaseObject.h"

ICollisionListner::ICollisionListner(BaseObject& owner)
    : m_pOwner(&owner)
{
}

ICollisionListner::~ICollisionListner()
{
}

BaseObject* ICollisionListner::GetOwner() const
{
    return m_pOwner;
}
