#include "stdafx.h"
#include "Ground.h"


Ground::Ground(int col, int row, float size)
	: m_col(col)
	, m_row(row)
	, m_size(size)
{

}


Ground::~Ground()
{
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pVB);
}

void Ground::Init()
{
	m_numVertices = (m_col + 1) * (m_row + 1); //총 정점 개수
	m_numIndices = m_col * m_row * 2 * 3;      //정사각형 하나는 각각 3개의 인덱스를 가진 2개의 삼각형으로 이뤄진다

	VERTEX_PC* pGroundVertex = new VERTEX_PC[m_numVertices];

	//시작위치
	int index = 0;
	D3DXVECTOR3 pos(-1.f * m_col * m_size * 0.5f, 0.f, m_row * m_size * 0.5f);
	for (int z = 0; z <= m_row; ++z)
	{
		for (int x = 0; x <= m_col; ++x)
		{
			pGroundVertex[index].p.x = pos.x + (m_size * x);
			pGroundVertex[index].p.y = 0.f;
			pGroundVertex[index].p.z = pos.z + -1.f * (m_size * z);
			pGroundVertex[index].c = D3DCOLOR_RGBA(255, 50, 255, 255);

			index++;
		}
	}

	//버텍스 버퍼 생성
	if (g_pDevice->CreateVertexBuffer(m_numVertices * sizeof(VERTEX_PC), 0, VERTEX_PC::FVF, D3DPOOL_DEFAULT, &m_pVB, 0) != D3D_OK)
	{
		MessageBox(NULL, TEXT("정점 버퍼 생성 Error"), TEXT("Error"), MB_OK);
		return;
	}

	void* pVertices;
	if (m_pVB->Lock(0, 0, &pVertices, NULL) != D3D_OK)
	{
		MessageBox(NULL, TEXT("정점 버퍼 lock Error"), TEXT("Error"), MB_OK);
		return;
	}

	memcpy(pVertices, pGroundVertex, m_numVertices * sizeof(VERTEX_PC));
	m_pVB->Unlock();

	//인덱스 버퍼 생성
	WORD* pIndex = new WORD[m_numIndices];
	index = 0;
	for (int z = 0; z < m_row; ++z)
	{
		for (int x = 0; x < m_col; ++x)
		{
			pIndex[index++] = WORD(z * (m_col + 1) + x);
			pIndex[index++] = WORD((z + 1) * (m_col + 1) + x + 1);
			pIndex[index++] = WORD((z + 1) * (m_col + 1) + x);

			pIndex[index++] = WORD(z * (m_col + 1) + x);
			pIndex[index++] = WORD(z * (m_col + 1) + x + 1);
			pIndex[index++] = WORD((z + 1) * (m_col + 1) + x + 1);
		}
	}

	void* pIndices;
	g_pDevice->CreateIndexBuffer(m_numIndices * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);
	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
	memcpy(pIndices, pIndex, sizeof(WORD) * m_numIndices);
	m_pIB->Unlock();

	delete[] pIndex;
	delete[] pGroundVertex;
}

void Ground::Update()
{
}

void Ground::Render()
{
	D3DXMatrixIdentity(&m_matWorld);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->SetIndices(m_pIB);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_numVertices, 0, m_numIndices / 3);
	
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
