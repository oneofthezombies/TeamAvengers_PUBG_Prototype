#pragma once

#include "IDisplayObject.h"

class MuzzleFlash : public IDisplayObject
{
private:
    LPDIRECT3DTEXTURE9 m_pTex;
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    bool m_isRender;
    float m_lifeTime;
    const float m_maxLifeTime;
    float m_pointScale;

public:
    MuzzleFlash();
    virtual ~MuzzleFlash();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    void Flash(const D3DXVECTOR3& pos);
};