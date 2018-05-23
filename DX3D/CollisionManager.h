#pragma once

#include "SingletonBase.h"

#define g_pCollisionManager CollisionManager::GetInstance()

class ICollidable;
class ColliderBase;
class BoxCollider;
class SphereCollider;
class ICollisionListner;

class CollisionManager
    : public SingletonBase<CollisionManager>
{
private:
    struct HashColliderBase
    {
        size_t operator()(const pair<ColliderBase*, ColliderBase*>& p) const
        {
            return hash<ColliderBase*>{}(p.first) ^ hash<ColliderBase*>{}(p.second);
        }
    };

    unordered_set<ICollidable*>                                         m_usetICollidable;

    unordered_set<ColliderBase*>                                        m_usetColliderBases;
    unordered_set<pair<ColliderBase*, ColliderBase*>, HashColliderBase> m_usetPrevCollisions;
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
    void NotifyCollisionAboutICollidables();

    void AddColliderBase(ColliderBase& val);
    void RemoveColliderBase(ColliderBase& val);
    void NotifyCollisionAboutColliderBases();

    void SetIsRender(const bool val);

    friend SingletonBase<CollisionManager>;
};