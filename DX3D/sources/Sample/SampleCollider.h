#pragma once

#include "Collider.h"
#include "IDisplayObject.h"

class BoxCollider;

class  SampleCollisionListener1 : public ICollisionListener
{
public:
    SampleCollisionListener1(BaseObject& owner);
    virtual ~SampleCollisionListener1();

    // Inherited via CollisionListener
    virtual void OnCollisionEnter(const ColliderBase& other) override;
    virtual void OnCollisionExit(const ColliderBase& other) override;
    virtual void OnCollisionStay(const ColliderBase& other) override;
};

class SampleCollisionListener2 : public ICollisionListener
{
public:
    SampleCollisionListener2(BaseObject& owner);
    virtual ~SampleCollisionListener2();

    // Inherited via CollisionListener
    virtual void OnCollisionEnter(const ColliderBase& other) override;
    virtual void OnCollisionExit(const ColliderBase& other) override;
    virtual void OnCollisionStay(const ColliderBase& other) override;
};

class SampleColliderOwner1 : public IDisplayObject
{
public:
    BoxCollider*             m_pBoxCollider;
    SampleCollisionListener1* m_pCollisionListener;

public:
    SampleColliderOwner1();
    virtual ~SampleColliderOwner1();

    // Inherited via IDisplayObject
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
};

class SampleColliderOwner2 : public IDisplayObject
{
public:
    BoxCollider*             m_pBoxCollider;
    SampleCollisionListener2* m_pCollisionListener;

public:
    SampleColliderOwner2();
    virtual ~SampleColliderOwner2();

    // Inherited via IDisplayObject
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
};