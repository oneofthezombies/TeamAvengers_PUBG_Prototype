#pragma once
#include "IDisplayObject.h"

class VertexBlending : public IDisplayObject
{
private:
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    WORD m_numVertices;
    D3DXMATRIX m_mat0;
    D3DXMATRIX m_mat1;
    D3DXMATRIX m_mat2;
    D3DXMATRIX m_mat3;
    LPDIRECT3DTEXTURE9 m_pTex;

public:
    VertexBlending();
    virtual ~VertexBlending();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
};