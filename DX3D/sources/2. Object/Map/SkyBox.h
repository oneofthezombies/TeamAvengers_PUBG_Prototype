#pragma once

#include "IDisplayObject.h"

class SkyBox : public IDisplayObject
{
private:
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    int                     m_numVertices;
    LPDIRECT3DINDEXBUFFER9  m_pIB;
    int                     m_numIndices;
    LPDIRECT3DTEXTURE9      m_pTex;

    void CreateVertices(vector<VERTEX_PT>& OutVertices, int& OutMemorySize);
    void CreateIndices(vector<WORD>& OutIndices, int& OutMemorySize);

public:
    SkyBox();
    virtual ~SkyBox();

    virtual void Init() override;
    void Init(const D3DXMATRIX& transform);

    virtual void Update() override;
    virtual void Render() override;
};