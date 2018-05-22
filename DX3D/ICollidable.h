#pragma once

#include "IDisplayObject.h"

class ColliderBase
{
public:
    enum Type
    {
        kBox,

        // Not yet used
        kSphere
    };

private:
    Type m_type;

protected:
    D3DXVECTOR3 m_vCenter;
    D3DCOLOR    m_color;

    ColliderBase(Type type);

public:
    virtual ~ColliderBase() = default;

    virtual void Render();
    Type GetType() const;
    void SetColor(const D3DCOLOR color);
    D3DXVECTOR3 GetCenter() const;
};

class SphereCollider : public ColliderBase
{
private:
    float m_radius;

public:
    SphereCollider();
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
    BoxCollider();
    virtual ~BoxCollider() = default;

    void Init(const D3DXVECTOR3& min, const D3DXVECTOR3& max);
    void Update(const D3DXMATRIXA16& transform);
    virtual void Render() override;

    D3DXVECTOR3 GetExtent() const;
    const D3DXMATRIXA16& GetTransform() const;
};

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
