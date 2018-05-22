#pragma once

#include "ICollidable.h"

class CollidablePlayerBox : public ICollidable
{
public:
    virtual void Init() override;
    virtual void Update() override;

    virtual void OnCollision(ICollidable & other) override;
};

class CollidableItemBox : public ICollidable
{
public:
    virtual void Init() override;
    virtual void Update() override;

    virtual void OnCollision(ICollidable & other) override;
};