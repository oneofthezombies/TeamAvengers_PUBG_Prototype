#pragma once

#include "SingletonBase.h"

#define g_pCollisionManager CollisionManager::GetInstance()

class ICollidable;
class BoxCollider;

class CollisionManager
    : public SingletonBase<CollisionManager>
{
private:
    unordered_set<ICollidable*> m_usetCollidable;
    bool m_bIsRender;

    CollisionManager();
    virtual ~CollisionManager() = default;

    bool HasCollision(const BoxCollider& lhs, const BoxCollider& rhs);

public:
    void Init();
    void Destroy();
    void Update();
    void Render();

    void AddCollidable(ICollidable& val);
    void RemoveCollidable(ICollidable& val);
    void NotifyCollision();
    void SetIsRender(const bool val);

    friend SingletonBase<CollisionManager>;
};