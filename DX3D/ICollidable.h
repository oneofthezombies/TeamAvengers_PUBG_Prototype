#pragma once

#include "IDisplayObject.h"

class ColliderBase
{
public:
    enum Type
    {
        Box,

        // Not yet used
        Sphere
    };

private:
    Type m_type;

protected:
    D3DCOLOR m_color;

    ColliderBase(Type type);

public:
    virtual ~ColliderBase() = default;

    virtual void Render();
    Type GetType() const;
    void SetColor(const D3DCOLOR color);
};

class SphereCollider
    : public ColliderBase
{
public:
    SphereCollider();
    virtual ~SphereCollider() = default;
};

class BoxCollider
    : public ColliderBase
{
private:
    D3DXVECTOR3 m_vCenter;
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
    void Update(const D3DXMATRIXA16* transform);
    virtual void Render() override;

    D3DXVECTOR3 GetCenter() const;
    D3DXVECTOR3 GetExtent() const;
    const D3DXMATRIXA16& GetTransform() const;
};

class ICollidable
    : public IDisplayObject
{
protected:
    ColliderBase* m_pCollider;

public:
    ICollidable();
    virtual ~ICollidable();

    // Inherited via IDisplayObject
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    virtual void OnCollision(ICollidable& other) = 0;
    ColliderBase* GetCollider() const;
};

class SampleCollidable
    : public ICollidable
{
public:
    virtual void Init() override;
    virtual void Update() override;

    // Inherited via ICollidable
    virtual void OnCollision(ICollidable & other) override;
};

class SampleCollidable2
    : public ICollidable
{
public:
    virtual void Init() override;
    virtual void Update() override;

    // Inherited via ICollidable
    virtual void OnCollision(ICollidable & other) override;
};