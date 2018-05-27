#pragma once

#include "IDisplayObject.h"

class Cubeman;

class CubemanBarrack : public IDisplayObject
{
private:
    unordered_set<Cubeman*> m_cubemans;

public:
    CubemanBarrack();
    virtual ~CubemanBarrack();
 
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    int GetNumCubemans();

    void RemoveCubeman(Cubeman& val);
};