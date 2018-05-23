#pragma once

class BaseObject;
class ICollisionListner;

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
    BaseObject*       m_pOwner;
    ICollisionListner* m_pListner;
    Type              m_type;

protected:
    D3DXVECTOR3 m_vCenter;
    D3DCOLOR    m_color;

    ColliderBase(Type type);
    void SetOwner(BaseObject& owner);

public:
    virtual ~ColliderBase();

    virtual void Render();
    Type GetType() const;
    void SetColor(const D3DCOLOR color);
    D3DXVECTOR3 GetCenter() const;
    BaseObject* GetOwner() const;
    void SetListner(ICollisionListner& listner);
    ICollisionListner* GetListner() const;
};

class SphereCollider : public ColliderBase
{
private:
    float m_radius;

public:
    SphereCollider();
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
    BoxCollider();
    BoxCollider(BaseObject& owner);
    virtual ~BoxCollider() = default;

    void Init(const D3DXVECTOR3& min, const D3DXVECTOR3& max);
    void Update(const D3DXMATRIXA16& transform);
    virtual void Render() override;

    D3DXVECTOR3 GetExtent() const;
    const D3DXMATRIXA16& GetTransform() const;
};

