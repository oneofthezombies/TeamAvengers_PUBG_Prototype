#pragma once

#include "Collider.h"
#include "IDisplayObject.h"

class BoxCollider;

class  SampleCollisionListner1 : public ICollisionListner
{
public:
    SampleCollisionListner1(BaseObject& owner);
    virtual ~SampleCollisionListner1();

    // Inherited via CollisionListner
    virtual void OnCollisionEnter(const ColliderBase& other) override;
    virtual void OnCollisionExit(const ColliderBase& other) override;
    virtual void OnCollisionStay(const ColliderBase& other) override;
};

class SampleCollisionListner2 : public ICollisionListner
{
public:
    SampleCollisionListner2(BaseObject& owner);
    virtual ~SampleCollisionListner2();

    // Inherited via CollisionListner
    virtual void OnCollisionEnter(const ColliderBase& other) override;
    virtual void OnCollisionExit(const ColliderBase& other) override;
    virtual void OnCollisionStay(const ColliderBase& other) override;
};

class SampleColliderOwner1 : public IDisplayObject
{
public:
    BoxCollider*             m_pBoxCollider;
    SampleCollisionListner1* m_pCollisionListner;

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
    SampleCollisionListner2* m_pCollisionListner;

public:
    SampleColliderOwner2();
    virtual ~SampleColliderOwner2();

    // Inherited via IDisplayObject
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
};