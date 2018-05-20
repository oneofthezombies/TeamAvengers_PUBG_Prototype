#include "stdafx.h"
#include "SkyBox.h"

void SkyBox::CreateVertices(vector<VERTEX_PT>& OutVertices, int& OutMemorySize)
{
    OutVertices.resize(24);

    /*
        5 ---- 6
       /|     /|
      / 4 ---/ 7
     1 ---- 2 /
     |/     |/
     0 ---- 3

    */

    OutVertices = 
    {
        // back 0123
        VERTEX_PT(-0.5f, -0.5f, -0.5f, /*0.0f, 0.0f, 1.0f,*/ 0.25f, 0.6666f),
        VERTEX_PT(-0.5f,  0.5f, -0.5f, /*0.0f, 0.0f, 1.0f,*/ 0.25f, 0.334f),
        VERTEX_PT(0.5f,  0.5f, -0.5f, /*0.0f, 0.0f, 1.0f,*/ 0.0f, 0.334f),
        VERTEX_PT(0.5f, -0.5f, -0.5f, /*0.0f, 0.0f, 1.0f,*/ 0.0f, 0.6666f),

        // front 7654
        VERTEX_PT( 0.5f, -0.5f, 0.5f, /*0.0f, 0.0f, -1.0f,*/ 0.75f, 0.6666f),
        VERTEX_PT( 0.5f,  0.5f, 0.5f, /*0.0f, 0.0f, -1.0f,*/ 0.75f, 0.334f),
        VERTEX_PT(-0.5f,  0.5f, 0.5f, /*0.0f, 0.0f, -1.0f,*/ 0.5f, 0.334f),
        VERTEX_PT(-0.5f, -0.5f, 0.5f, /*0.0f, 0.0f, -1.0f,*/ 0.5f, 0.6666f),

        // left 4510
        VERTEX_PT(-0.5f, -0.5f,  0.5f, /*1.0f, 0.0f, 0.0f,*/ 0.5f, 0.6666f),
        VERTEX_PT(-0.5f,  0.5f,  0.5f, /*1.0f, 0.0f, 0.0f,*/ 0.5f, 0.334f),
        VERTEX_PT(-0.5f,  0.5f, -0.5f, /*1.0f, 0.0f, 0.0f,*/ 0.25f, 0.334f),
        VERTEX_PT(-0.5f, -0.5f, -0.5f, /*1.0f, 0.0f, 0.0f,*/ 0.25f, 0.6666f),

        // right 3267
        VERTEX_PT(0.5f, -0.5f, -0.5f, /*-1.0f, 0.0f, 0.0f,*/ 1.0f, 0.6666f),
        VERTEX_PT(0.5f,  0.5f, -0.5f, /*-1.0f, 0.0f, 0.0f,*/ 1.0f, 0.334f),
        VERTEX_PT(0.5f,  0.5f,  0.5f, /*-1.0f, 0.0f, 0.0f,*/ 0.75f, 0.334f),
        VERTEX_PT(0.5f, -0.5f,  0.5f, /*-1.0f, 0.0f, 0.0f,*/ 0.75, 0.6666f),

        // down 7403
        VERTEX_PT( 0.5f, -0.5f,  0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.5f, 1.0f),
        VERTEX_PT(-0.5f, -0.5f,  0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.5f, 0.6666f),
        VERTEX_PT(-0.5f, -0.5f, -0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.25f, 0.6666f),
        VERTEX_PT( 0.5f, -0.5f, -0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.25f, 1.0f),

        // up 5621
        VERTEX_PT(-0.5f, 0.5f,  0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.5f, 0.3333f),
        VERTEX_PT( 0.5f, 0.5f,  0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.5f, 0.0f),
        VERTEX_PT( 0.5f, 0.5f, -0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.25f, 0.0f),
        VERTEX_PT(-0.5f, 0.5f, -0.5f, /*0.0f, -1.0f, 0.0f,*/ 0.25f, 0.3333f),
    };

    OutMemorySize = OutVertices.size() * sizeof VERTEX_PT;
}

void SkyBox::CreateIndices(vector<WORD>& OutIndices, int& OutMemorySize)
{
    OutIndices.resize(36);

    OutIndices = 
    {
        // back
        0, 2, 1, 0, 3, 2,

        // front
        4, 6, 5, 4, 7, 6,

        // left
        8, 10, 9, 8, 11, 10,

        // right
        12, 14, 13, 12, 15, 14,

        // down
        16, 18, 17, 16, 19, 18,

        // up
        20, 22, 21, 20, 23, 22,
    };

    OutMemorySize = OutIndices.size() * sizeof WORD;
}

SkyBox::SkyBox()
    : IDisplayObject()
    , m_pVB(nullptr)
    , m_pIB(nullptr)
    , m_numVertices(0)
    , m_numIndices(0)
{
}

SkyBox::~SkyBox()
{
    SAFE_RELEASE(m_pVB);
    SAFE_RELEASE(m_pIB);
}

void SkyBox::Init()
{
    // do nothing

    MessageBox(NULL, TEXT("Do not use this method. use SkyBox::Init(const D3DXMATRIXA16* transform)"), 0, 0);
}

void SkyBox::Init(const D3DXMATRIXA16* transform)
{
    m_pTex = g_pTextureManager->GetTexture("resources/images/skybox002.png");

    int verticesMemorySize = 0;
    vector<VERTEX_PT> vertices;
    CreateVertices(vertices, verticesMemorySize);
    m_numVertices = vertices.size();

    const auto dv = g_pDevice;
    dv->CreateVertexBuffer(verticesMemorySize, D3DUSAGE_WRITEONLY, VERTEX_PT::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);

    if (transform)
    {
        for (auto& v : vertices)
            D3DXVec3TransformCoord(&v.p, &v.p, transform);
    }

    VERTEX_PT* vb;
    m_pVB->Lock(0, 0, (LPVOID*)&vb, D3DLOCK_DISCARD);
    MoveMemory(vb, vertices.data(), verticesMemorySize);
    m_pVB->Unlock();

    int indicesMemorySize = 0;
    vector<WORD> indices;
    CreateIndices(indices, indicesMemorySize);
    m_numIndices = indices.size();

    dv->CreateIndexBuffer(indicesMemorySize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL);

    WORD* ib;
    m_pIB->Lock(0, 0, (LPVOID*)&ib, D3DLOCK_DISCARD);
    MoveMemory(ib, indices.data(), indicesMemorySize);
    m_pIB->Unlock();
}

void SkyBox::Update()
{
    // do nothing
}

void SkyBox::Render()
{
    const auto dv = g_pDevice;
    dv->SetRenderState(D3DRS_LIGHTING, false);
    dv->SetTransform(D3DTS_WORLD, &m_matWorld);
    dv->SetTexture(0, m_pTex);
    dv->SetFVF(VERTEX_PT::FVF);
    dv->SetStreamSource(0, m_pVB, 0, sizeof VERTEX_PT);
    dv->SetIndices(m_pIB);
    dv->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_numVertices, 0, m_numIndices / 3);
    dv->SetTexture(0, NULL);
    dv->SetRenderState(D3DRS_LIGHTING, true);
}
