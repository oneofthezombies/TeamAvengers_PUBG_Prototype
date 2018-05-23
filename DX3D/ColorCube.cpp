#include "stdafx.h"
#include "ColorCube.h"


ColorCube::ColorCube()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_pVB = NULL;
	m_pIB = NULL;
}


ColorCube::~ColorCube()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
}

void ColorCube::Init()
{
	vector<D3DXVECTOR3> vecPos;
	for (size_t i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecPos.push_back(g_aCubeVertex[i]);
	}

	//SetVertex(m_vecVertex, vecPos); return;
	
	SetVertex(m_vecVertex, m_vecIndex, vecPos);
	SetBuffer(m_pVB, m_pIB, m_vecVertex, m_vecIndex);

	m_pVB->GetDesc(&m_VBDesc);
	m_pIB->GetDesc(&m_IBDesc);

    D3DXMATRIXA16 matT;
    D3DXMatrixTranslation(&matT, 0, 2, 10);
    m_matWorld = matT;
}

void ColorCube::Update()
{
	m_rot.y += 0.01f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, m_rot.y);
	m_matWorld = matR;
}

void ColorCube::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	/*
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0], sizeof(VERTEX_PC)); return;
		*/
	/*
	g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0,
		m_vecVertex.size(), m_vecIndex.size() / 3, &m_vecIndex[0],
		D3DFMT_INDEX16, &m_vecVertex[0], sizeof(VERTEX_PC));return;
		*/
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->SetIndices(m_pIB);
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		m_VBDesc.Size, 0, m_IBDesc.Size / 3);
}


void ColorCube::SetVertex(vector<VERTEX_PC>& vecVertexOut,
	vector<D3DXVECTOR3> vecPos)
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);

	vector<VERTEX_PC> vec;
	vec.push_back(VERTEX_PC(vecPos[0], white));
	vec.push_back(VERTEX_PC(vecPos[1], yellow));
	vec.push_back(VERTEX_PC(vecPos[2], green));
	vec.push_back(VERTEX_PC(vecPos[3], blue));
	vec.push_back(VERTEX_PC(vecPos[4], white));
	vec.push_back(VERTEX_PC(vecPos[5], yellow));
	vec.push_back(VERTEX_PC(vecPos[6], red));
	vec.push_back(VERTEX_PC(vecPos[7], green));

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecVertexOut.push_back(vec[g_aCubeIndex[i]]);
	}
}

void ColorCube::SetVertex(vector<VERTEX_PC>& vecVertexOut,
	vector<WORD>& vecIndexOut, vector<D3DXVECTOR3> vecPos)
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);

	vecVertexOut.push_back(VERTEX_PC(vecPos[0], blue));
	vecVertexOut.push_back(VERTEX_PC(vecPos[1], red));
	vecVertexOut.push_back(VERTEX_PC(vecPos[2], green));
	vecVertexOut.push_back(VERTEX_PC(vecPos[3], red));
	vecVertexOut.push_back(VERTEX_PC(vecPos[4], blue));
	vecVertexOut.push_back(VERTEX_PC(vecPos[5], red));
	vecVertexOut.push_back(VERTEX_PC(vecPos[6], green));
	vecVertexOut.push_back(VERTEX_PC(vecPos[7], red));

	for (size_t i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecIndexOut.push_back(g_aCubeIndex[i]);
	}
}

void ColorCube::SetBuffer(LPDIRECT3DVERTEXBUFFER9 & pVb, 
	LPDIRECT3DINDEXBUFFER9 & pIb, 
	vector<VERTEX_PC>& vecVertex, vector<WORD>& vecIndex)
{
	g_pDevice->CreateVertexBuffer(vecVertex.size() * sizeof(VERTEX_PC),
		0, VERTEX_PC::FVF, D3DPOOL_MANAGED, &pVb, NULL);

	VERTEX_PC* pVertex;
	pVb->Lock(0, 0, (LPVOID*)&pVertex, 0);
	memcpy(pVertex, &vecVertex[0], vecVertex.size() * sizeof(VERTEX_PC));
	pVb->Unlock();
	vecVertex.clear();

	g_pDevice->CreateIndexBuffer(vecIndex.size() * sizeof(WORD),
		NULL, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIb, NULL);

	WORD* pIndex;
	pIb->Lock(0, 0, (LPVOID*)&pIndex, 0);
	memcpy(pIndex, &vecIndex[0], vecIndex.size() * sizeof(WORD));
	pIb->Unlock();
	vecIndex.clear();
}
