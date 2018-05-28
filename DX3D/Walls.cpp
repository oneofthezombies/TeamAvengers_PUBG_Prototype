#include "stdafx.h"
#include "Walls.h"


Walls::Walls()
{
}


Walls::~Walls()
{
}

void Walls::Init()
{
	vector<D3DXVECTOR3> vecWall;
	vecWall.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	vecWall.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	vecWall.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));
	vecWall.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	vecWall.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));
	vecWall.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));

	MakePlaneGroup(m_vecWall0, vecWall);
	MakePlaneGroup(m_vecWall1, vecWall);

	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, 5, 0, 0);
	for (size_t i = 0; i < m_vecWall0.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecWall1[i].p, &m_vecWall1[i].p, &matT);
	}

	MakePlaneGroup(m_vecWall2, vecWall);

	D3DXMatrixTranslation(&matT, -5, 0, 0);
	for (size_t i = 0; i < m_vecWall0.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecWall2[i].p, &m_vecWall2[i].p, &matT);
	}


	for (auto p : m_vecWall0)
		m_vecWalls.push_back(p);

	for (auto p : m_vecWall1)
		m_vecWalls.push_back(p);

	for (auto p : m_vecWall2)
		m_vecWalls.push_back(p);


	{
		D3DLIGHT9 light;
		D3DXVECTOR3 pos(0.0f, 1.0f, -3.0f);
		D3DXCOLOR c = RED;
		light = DXUtil::InitPoint(&pos, &c);
		light.Range = 4.0f;
		g_pDevice->SetLight(1, &light);
		g_pDevice->LightEnable(1, true);
	}
	{
		D3DLIGHT9 light;
		D3DXVECTOR3 pos(-5.0f, 3.0f, -15.0f);
		D3DXVECTOR3 dir(0.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&dir, &dir);
		D3DXCOLOR c = BLUE;
		light = DXUtil::InitSpot(&dir, &pos, &c);
		light.Range = 15.0f;
		g_pDevice->SetLight(2, &light);
		g_pDevice->LightEnable(2, true);
	}

	vector<D3DXVECTOR3> vecFloor;
	vecFloor.push_back(D3DXVECTOR3(-1.0f, 0.0f, -1.0f));
	vecFloor.push_back(D3DXVECTOR3(-1.0f, 0.0f, 1.0f));
	vecFloor.push_back(D3DXVECTOR3(1.0f, 0.0f, 1.0f));
	vecFloor.push_back(D3DXVECTOR3(1.0f, 0.0f, -1.0f));
	/*
	m_vecFloor.push_back(VERTEX_PN(vecFloor[0], D3DXVECTOR3(0, 1, 0)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[1], D3DXVECTOR3(0, 1, 0)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[2], D3DXVECTOR3(0, 1, 0)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[0], D3DXVECTOR3(0, 1, 0)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[2], D3DXVECTOR3(0, 1, 0)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[3], D3DXVECTOR3(0, 1, 0)));
	*/
	/**/
	m_vecFloor.push_back(VERTEX_PN(vecFloor[0], D3DXVECTOR3(-1, 1, -1)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[1], D3DXVECTOR3(-1, 1, 1)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[2], D3DXVECTOR3(1, 1, 1)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[0], D3DXVECTOR3(-1, 1, -1)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[2], D3DXVECTOR3(1, 1, 1)));
	m_vecFloor.push_back(VERTEX_PN(vecFloor[3], D3DXVECTOR3(1, 1, -1)));
	
	{
		D3DXMATRIX matS, matT;
		D3DXMatrixScaling(&matS, 10, 10, 10);
		D3DXMatrixTranslation(&matT, 0, 0, -5);
		for (size_t i = 0; i < m_vecFloor.size(); i++)
		{
			D3DXVec3TransformCoord(&m_vecFloor[i].p, &m_vecFloor[i].p, &(matS *matT));
		}
	}
}

void Walls::Update()
{
}

void Walls::Render()
{
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetFVF(VERTEX_PN::FVF);
	g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecWalls.size() / 3,
		&m_vecWalls[0], sizeof(VERTEX_PN));

	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecFloor.size() / 3,
		&m_vecFloor[0], sizeof(VERTEX_PN));
}

void Walls::MakePlane(vector<VERTEX_PN>& vecOut, vector<D3DXVECTOR3> &vecPos, D3DXMATRIX &mat)
{
	D3DXVECTOR3 tmpVec3;
	D3DXVECTOR3 normal;

	for (size_t i = 0; i < vecPos.size(); i++)
	{
		if (i % 6 == 0)
			DXUtil::ComputeNormal(&normal, &vecPos[0], &vecPos[1], &vecPos[2]);

		D3DXVec3TransformCoord(&tmpVec3, &vecPos[i], &mat);
		vecOut.push_back(VERTEX_PN(tmpVec3, normal));
	}
}

void Walls::MakePlaneGroup(vector<VERTEX_PN>& vecOut, vector<D3DXVECTOR3> vecWall)
{
	D3DXMATRIX matS, matR, matT, mat;
	float size = 1.5;
	D3DXMatrixScaling(&matS, size, size, size);
	D3DXMatrixTranslation(&matT, 0, size, 0);
	mat = matS * matT;
	MakePlane(vecOut, vecWall, mat);

	D3DXMatrixScaling(&matS, size, size, size);
	D3DXMatrixRotationY(&matR, D3DX_PI / 3.0f);
	D3DXMatrixTranslation(&matT, size * 2, size, -size);
	mat = matS * matR * matT;
	MakePlane(vecOut, vecWall, mat);

	D3DXMatrixScaling(&matS, size, size, size);
	D3DXMatrixRotationY(&matR, -D3DX_PI / 3.0f);
	D3DXMatrixTranslation(&matT, -size * 2, size, -size);
	mat = matS * matR * matT;
	MakePlane(vecOut, vecWall, mat);
}