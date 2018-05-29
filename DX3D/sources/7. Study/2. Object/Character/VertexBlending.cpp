#include "stdafx.h"
#include "VertexBlending.h"

VertexBlending::VertexBlending()
{
}

VertexBlending::~VertexBlending()
{
    SAFE_RELEASE(m_pVB);
    SAFE_RELEASE(m_pTex);
}

void VertexBlending::Init()
{
    m_numVertices = 100;

    int numHalfVertices = m_numVertices / 2;
    float weight1[3] = { 0.5f, 0.5f, 0.0f };
    float weight2[3] = { 1.0f, 0.0f, 0.0f };

    g_pDevice->CreateVertexBuffer(m_numVertices * sizeof VERTEX_BLENDING, 0, VERTEX_BLENDING::FVF, D3DPOOL_DEFAULT, &m_pVB, NULL);

    VERTEX_BLENDING* pV;
    m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
    for (int i = 0; i < numHalfVertices; ++i)
    {
        // 0 40 80 120 160 200 240 280 320 360
        float theta = (2.0f * D3DX_PI * i) / (float)(numHalfVertices - 1);

        pV[2 * i + 0] = VERTEX_BLENDING(D3DXVECTOR3(cos(theta), 1.0, sin(theta)), 
                                        weight1, 
                                        0x00000100, 
                                        D3DXVECTOR2(i / (float)(numHalfVertices - 1), 0));

        pV[2 * i + 1] = VERTEX_BLENDING(D3DXVECTOR3(cos(theta), -1.0, sin(theta)), 
                                        weight2, 
                                        0x00000100, 
                                        D3DXVECTOR2(i / (float)(numHalfVertices - 1), 1));
    }
    m_pVB->Unlock();
    m_pTex = g_pTextureManager->GetTexture("resources/images/ham2.png");
}

void VertexBlending::Update()
{
    D3DXMatrixIdentity(&m_mat0);
    DWORD d = GetTickCount() % ((int)(D3DX_PI * 2 * 1000));
    cout << d << endl;
    D3DXMatrixRotationY(&m_mat1, d / 1000.0);
    D3DXMatrixScaling(&m_mat2, 0.5 * sin(d / 1000.0), 0, 0.5 * sin(d / 1000.0));
}

void VertexBlending::Render()
{
    g_pDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, true);
    g_pDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_3WEIGHTS);
    g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

    g_pDevice->SetTransform(D3DTS_WORLDMATRIX(0), &m_mat0);
    g_pDevice->SetTransform(D3DTS_WORLDMATRIX(1), &m_mat1);
    g_pDevice->SetTransform(D3DTS_WORLDMATRIX(2), &m_mat2);
    g_pDevice->SetTransform(D3DTS_WORLDMATRIX(3), &m_mat3);
    g_pDevice->SetTexture(0, m_pTex);
    g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof VERTEX_BLENDING);
    g_pDevice->SetFVF(VERTEX_BLENDING::FVF);
    g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_numVertices - 2);

    g_pDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, false);
    g_pDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
    g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
