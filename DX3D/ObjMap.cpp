#include "stdafx.h"
#include "ObjMap.h"
#include "DrawingGroup.h"
#include "ObjLoader.h"

ObjMap::ObjMap()
{
	m_rayOffsetY = 2;
}


ObjMap::~ObjMap()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RELEASE(p);
	SAFE_RELEASE(m_pMeshMap);
}

void ObjMap::Init()
{
	D3DXMATRIX matRX, matRY, matS, matWorld;
	D3DXMatrixRotationX(&matRX, -D3DX_PI / 2.0f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	matWorld = matS * matRX * matRY;

	ObjLoader loader;
	loader.Load("resources/obj", "map.obj", &matWorld, m_vecDrawingGroup);
	//loader.Load("resources/obj", "map_surface.obj", &matWorld, m_vecDrawingGroup);

	//m_pMeshMap = loader.LoadMesh("resources/obj", "map.obj", &matWorld, m_vecMtlTex);

	loader.LoadSurface("resources/obj/map_surface.obj",
		&matWorld, m_vecVertex);
	g_pMapManager->AddMap("ObjMap", this);
	g_pMapManager->SetCurrentMap("ObjMap");
}

void ObjMap::Update()
{
}

void ObjMap::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	RenderDrawingGroup();
	//RenderMesh();
	//RenderDrawSpeed();
	//RenderEachSubset();
}

bool ObjMap::GetHeight(OUT float & height, const D3DXVECTOR3 & pos)
{
	D3DXVECTOR3 rayPos(pos.x, pos.y + m_rayOffsetY, pos.z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float distance;

	for (size_t i = 0; i < m_vecVertex.size(); i+= 3)
	{
		if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1],
			&m_vecVertex[i + 2], &rayPos, &rayDir, 0, 0, &distance))
		{
			height = rayPos.y - distance;
			return true;
		}
	}
	return false;
}

void ObjMap::RenderDrawingGroup()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RENDER(p);
}

void ObjMap::RenderMesh()
{
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
		g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
		m_pMeshMap->DrawSubset(i);
	}
}

void ObjMap::RenderEachSubset()
{
	static int nSubSet = 0;

	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		--nSubSet;
		if (nSubSet < 0) nSubSet = 0;
	}
	else if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		++nSubSet;
		if (static_cast<size_t>(nSubSet) > m_vecMtlTex.size() - 1) nSubSet = m_vecMtlTex.size() - 1;
	}

	g_pDevice->SetMaterial(&m_vecMtlTex[nSubSet]->GetMaterial());
	g_pDevice->SetTexture(0, m_vecMtlTex[nSubSet]->GetTexture());
	m_pMeshMap->DrawSubset(nSubSet);
}

void ObjMap::RenderDrawSpeed()
{
	DWORD start, finish;
	size_t drawCount = 100;
	start = GetTickCount();
	for (size_t cnt = 0; cnt < drawCount; cnt++)
	{
		RenderDrawingGroup();
	}
	finish = GetTickCount();

	static float sumTimeDrawingGroup = 0;
	sumTimeDrawingGroup += (finish - start) / 1000.0f;

	start = GetTickCount();
	for (size_t cnt = 0; cnt < drawCount; cnt++)
	{
		RenderMesh();
	}
	finish = GetTickCount();

	static float sumTimeMesh = 0;
	sumTimeMesh += (finish - start) / 1000.0f;

	Debug->AddText(sumTimeDrawingGroup);
	Debug->AddText(" / ");
	Debug->AddText(sumTimeMesh);
	Debug->AddText(" = ");
	Debug->AddText(sumTimeDrawingGroup / sumTimeMesh);
	Debug->EndLine();
}
