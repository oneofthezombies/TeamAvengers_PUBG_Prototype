#pragma once
#include "IDisplayObject.h"
class VertexBlending :
    public IDisplayObject
{
private:
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    WORD                    m_numVertices;
    D3DXMATRIXA16           m_mat0;
    D3DXMATRIXA16           m_mat1;
    D3DXMATRIXA16           m_mat2;
    D3DXMATRIXA16           m_mat3;
    LPDIRECT3DTEXTURE9      m_pTex;

public:
    VertexBlending();
    virtual ~VertexBlending();

    // Inherited via IDisplayObject
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
};

