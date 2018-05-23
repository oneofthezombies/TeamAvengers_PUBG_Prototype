#pragma once

#include "IDisplayObject.h"

class ColliderBase;

class ICollidable : public IDisplayObject
{
private:
    ColliderBase* m_pCollider;

public:
    ICollidable();
    virtual ~ICollidable();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    virtual void OnCollision(ICollidable& other) = 0;

    BoxCollider& SetCollider(const D3DXVECTOR3& min, const D3DXVECTOR3& max);
    SphereCollider& SetCollider(const float radius);
    ColliderBase* GetCollider() const;
};
