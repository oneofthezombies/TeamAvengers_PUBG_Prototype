#pragma once

#include "SingletonBase.h"

#define g_pCollisionManager CollisionManager::GetInstance()

class ICollidable;
class BoxCollider;
class SphereCollider;

class CollisionManager
    : public SingletonBase<CollisionManager>
{
private:
    unordered_set<ICollidable*> m_usetICollidable;
    bool m_bIsRender;

    CollisionManager();
    virtual ~CollisionManager() = default;

    bool HasCollision(const BoxCollider& lhs, const BoxCollider& rhs);

    // no impl
    bool HasCollision(const BoxCollider& lhs, const SphereCollider& rhs);

    // no impl
    bool HasCollision(const SphereCollider& lhs, const BoxCollider& rhs);

    // no impl
    bool HasCollision(const SphereCollider& lhs, const SphereCollider& rhs);

public:
    void Init();
    void Destroy();
    void Update();
    void Render();

    void AddICollidable(ICollidable& val);
    void RemoveICollidable(ICollidable& val);
    void NotifyCollision();
    void SetIsRender(const bool val);

    friend SingletonBase<CollisionManager>;
};