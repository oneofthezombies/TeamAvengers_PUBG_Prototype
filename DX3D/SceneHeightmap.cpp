#include "stdafx.h"
#include "SceneHeightmap.h"
#include "HeightMap.h"
#include "AseCharacter.h"
#include "Picking.h"
#include "SampleUI.h"


SceneHeightmap::SceneHeightmap()
{
	m_pHeightMap = NULL;
	m_pAseCharacter = NULL;
	m_pPicking = NULL;
	m_pAStar = NULL;
}


SceneHeightmap::~SceneHeightmap()
{
	OnDestructIScene();
}

void SceneHeightmap::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2f, 0.03f, 0.2f);

	m_pHeightMap = new HeightMap; AddSimpleDisplayObj(m_pHeightMap);
	m_pHeightMap->SetDimension(257);
	m_pHeightMap->Load("resources/heightmap/HeightMap.raw", &matS);
	m_pHeightMap->Init();
	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;
	m_pHeightMap->SetMtlTex(mtl,
		g_pTextureManager->GetTexture(string("resources/heightmap/terrain.jpg")));

	g_pMapManager->AddMap("heightmap", m_pHeightMap);
	g_pMapManager->SetCurrentMap("heightmap");

	m_pAseCharacter = new AseCharacter; m_pAseCharacter->Init();
	AddSimpleDisplayObj(m_pAseCharacter);

	m_pPicking = new Picking; m_pPicking->Init();
	AddSimpleDisplayObj(m_pPicking);

	//IDisplayObject* pObj = new SampleUI; pObj->Init();
	//AddSimpleDisplayObj(pObj);


	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void SceneHeightmap::Update()
{
	OnUpdateIScene();
}

void SceneHeightmap::Render()
{
	OnRenderIScene();
}

void SceneHeightmap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pHeightMap);
	SAFE_WNDPROC(m_pPicking);
}
