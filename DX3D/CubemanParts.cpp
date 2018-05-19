#include "stdafx.h"
#include "CubemanParts.h"


CubemanParts::CubemanParts(float rotXSpeed)
{
	m_rotXSpeed = rotXSpeed;
}

CubemanParts::~CubemanParts()
{
	SAFE_RELEASE(m_tex);
}

void CubemanParts::Init()
{
}

void CubemanParts::Init(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV)
{
	vector<D3DXVECTOR3> vecVertex;
	for (int i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecVertex.push_back(g_aCubeVertex[i]);
	}
	
	if (pMat)
	{
		for (int i = 0; i < vecVertex.size(); i++)
		{
			D3DXVec3TransformCoord(&vecVertex[i],
				&vecVertex[i], pMat);
		}
	}
	D3DXCreateTextureFromFile(g_pDevice, _T("resources/textures/naked.png"), &m_tex);
	//SetPCVertex(m_vecPCVertex, vecVertex);
	SetPTVertex(m_vecPTVertex, vecVertex, vecUV);
}

void CubemanParts::Update()
{
	D3DXMATRIXA16 matR, matT;

	if (m_isMoving)
		m_rotXAngle += m_rotXSpeed;

	if (m_rotXAngle < -D3DX_PI / 4.0f)
	{
		m_rotXSpeed *= -1;
		m_rotXAngle = -D3DX_PI / 4.0f;
	}
	if (m_rotXAngle > D3DX_PI / 4.0f)
	{
		m_rotXSpeed *= -1;
		m_rotXAngle = D3DX_PI / 4.0f;
	}
	D3DXMatrixRotationX(&matR, m_rotXAngle);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	m_matWorld = matR * matT;

	if (m_pParent)
	{
		m_matWorld = m_matWorld * m_pParent->GetWorldMatrix();
	}

	for (auto child : m_vecPChild)
	{
		child->Update();
	}
}

void CubemanParts::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (m_vecPCVertex.empty() == false)
	{
		g_pDevice->SetTexture(0, NULL);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecPCVertex.size() / 3,
			&m_vecPCVertex[0], sizeof(VERTEX_PC));
	}
	else if (m_vecPTVertex.empty() == false)
	{
		g_pDevice->SetTexture(0, m_tex);
		g_pDevice->SetFVF(VERTEX_PT::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecPTVertex.size() / 3,
			&m_vecPTVertex[0], sizeof(VERTEX_PT));
	}

	for (auto child : m_vecPChild)
	{
		child->Render();
	}
}



void CubemanParts::SetPCVertex(vector<VERTEX_PC>& vecOut, vector<D3DXVECTOR3>& vecVertex)
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);

	vector<VERTEX_PC> vec;
	vec.push_back(VERTEX_PC(vecVertex[0], white));
	vec.push_back(VERTEX_PC(vecVertex[1], yellow));
	vec.push_back(VERTEX_PC(vecVertex[2], green));
	vec.push_back(VERTEX_PC(vecVertex[3], blue));
	vec.push_back(VERTEX_PC(vecVertex[4], white));
	vec.push_back(VERTEX_PC(vecVertex[5], yellow));
	vec.push_back(VERTEX_PC(vecVertex[6], red));
	vec.push_back(VERTEX_PC(vecVertex[7], green));

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecOut.push_back(vec[g_aCubeIndex[i]]);
	}
}

void CubemanParts::SetPTVertex(vector<VERTEX_PT>& vecOut, vector<D3DXVECTOR3>& vecVertex, vector<vector<int>>& uv)
{
	vector<D3DXVECTOR2> vecUV4Vertex;
	MakeUVList(vecUV4Vertex, uv);

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecOut.push_back(VERTEX_PT(vecVertex[g_aCubeIndex[i]], vecUV4Vertex[i]));
	}
}

void CubemanParts::SetMovingState(bool isMoving)
{
	if (m_isMoving == isMoving)
		return;

	m_isMoving = isMoving;

	if (m_isMoving == false)
	{
		m_rotXAngle = 0;
	}

	for (auto child : m_vecPChild)
	{
		static_cast<CubemanParts*>(child)
			->SetMovingState(m_isMoving);
	}
}

void CubemanParts::MakeUVList(vector<D3DXVECTOR2>& out,
	vector<vector<int>>& uv)
{
	for (size_t i = 0; i < uv.size(); i++)
	{
		out.push_back(D3DXVECTOR2(uv[i][0] / 64.0f, uv[i][1] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][2] / 64.0f, uv[i][3] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][4] / 64.0f, uv[i][5] / 32.0f));

		out.push_back(D3DXVECTOR2(uv[i][0] / 64.0f, uv[i][1] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][4] / 64.0f, uv[i][5] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][6] / 64.0f, uv[i][7] / 32.0f));
	}
}
