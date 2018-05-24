#pragma once
#include "ComponentBase.h"
#include "CollisionManager.h"

class BaseObject;
class ICollisionListner;

class ColliderBase : public ComponentBase
{
public:
    enum Type
    {
        kBox,

        // Not yet used
        kSphere
    };

private:
    ICollisionListner* m_pListner;
    Type               m_type;
    CollisionTag       m_tag;

protected:
    D3DXVECTOR3 m_vCenter;
    D3DCOLOR    m_color;

    ColliderBase(BaseObject& owner, const Type type);

public:
    virtual ~ColliderBase();

    virtual void Render();
    Type GetType() const;
    void SetColor(const D3DCOLOR color);
    D3DXVECTOR3 GetCenter() const;
    
    void               SetListner(ICollisionListner& listner);
    ICollisionListner* GetListner() const;

    void         SetTag(const CollisionTag tag);
    CollisionTag GetTag() const;
};

class SphereCollider : public ColliderBase
{
private:
    float m_radius;

public:
    SphereCollider(BaseObject& owner);
    virtual ~SphereCollider() = default;

    void Init(const float radius);
    void Update(const D3DXMATRIXA16& transform);
    virtual void Render() override;
};

class BoxCollider : public ColliderBase
{
private:
    D3DXVECTOR3 m_vExtent;

    // row 0 : x, y and z of axis 0
    // row 1 : x, y and z of axis 1
    // row 2 : x, y and z of axis 2
    // row 3 : x, y and z of translation
    D3DXMATRIXA16 m_mTransform;

public:
    BoxCollider(BaseObject& owner);
    virtual ~BoxCollider();

    void Init(const D3DXVECTOR3& min, const D3DXVECTOR3& max);
    void Update(const D3DXMATRIXA16& transform);
    virtual void Render() override;

    void Move(const D3DXVECTOR3& val);

    D3DXVECTOR3 GetExtent() const;
    const D3DXMATRIXA16& GetTransform() const;
};

class ICollisionListner : public ComponentBase
{
protected:
    ICollisionListner(BaseObject& owner);

public:
    virtual ~ICollisionListner();

    virtual void OnCollisionEnter(const ColliderBase& other) = 0;
    virtual void OnCollisionExit(const ColliderBase& other) = 0;
    virtual void OnCollisionStay(const ColliderBase& other) = 0;
};