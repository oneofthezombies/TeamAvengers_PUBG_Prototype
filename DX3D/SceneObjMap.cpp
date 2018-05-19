#include "stdafx.h"
#include "SceneObjMap.h"
#include "ObjMap.h"
#include "Cubeman.h"
#include "AseCharacter.h"

SceneObjMap::SceneObjMap()
{
	m_pObjMap = NULL;
	m_pCubeman = NULL;
	m_pAseCharacter = NULL;
}


SceneObjMap::~SceneObjMap()
{
	OnDestructIScene();
}

void SceneObjMap::Init()
{
	m_pObjMap = new ObjMap; m_pObjMap->Init(); 
	AddSimpleDisplayObj(m_pObjMap);
	//m_pCubeman = new Cubeman; m_pCubeman->Init();
	AddSimpleDisplayObj(m_pCubeman);
	m_pAseCharacter = new AseCharacter; m_pAseCharacter->Init();
	AddSimpleDisplayObj(m_pAseCharacter);
	
	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void SceneObjMap::Update()
{
	OnUpdateIScene();
}

void SceneObjMap::Render()
{
	OnRenderIScene();
}

void SceneObjMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
