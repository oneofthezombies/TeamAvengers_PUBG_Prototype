#pragma once

class BaseObject;
class ColliderBase;

class ICollisionListner
{
private:
    BaseObject* m_pOwner;

protected:
    ICollisionListner(BaseObject& owner);

public:
    virtual ~ICollisionListner();

    virtual void OnCollisionEnter(const ColliderBase& other) = 0;
    virtual void OnCollisionExit(const ColliderBase& other) = 0;
    virtual void OnCollisionStay(const ColliderBase& other) = 0;

    BaseObject* GetOwner() const;
};