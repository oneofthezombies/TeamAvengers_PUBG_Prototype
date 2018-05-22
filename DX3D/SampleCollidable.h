#pragma once

#include "ICollidable.h"

class UIObject;

class CollidablePlayerBox : public ICollidable
{
private:
    BoxCollider* bc;

public:
    CollidablePlayerBox();
    virtual ~CollidablePlayerBox() = default;

    virtual void Init() override;
    virtual void Update() override;

    virtual void OnCollision(ICollidable& other) override;
};

class CollidableItemBox : public ICollidable
{
private:
    BoxCollider* bc;
    UIObject* uiim;

public:
    CollidableItemBox();
    virtual ~CollidableItemBox() = default;

    virtual void Init() override;
    virtual void Update() override;

    virtual void OnCollision(ICollidable& other) override;
};
