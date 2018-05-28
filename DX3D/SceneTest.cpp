#include "stdafx.h"
#include "SceneTest.h"
#include "Frustum.h"
#include "Grid.h"
#include "ParticleTest.h"
#include "SkyBox.h"
#include "UIText.h"
#include "SkinnedMesh.h"

SceneTest::SceneTest()
{
	m_pGrid = NULL;
}

SceneTest::~SceneTest()
{
	SAFE_RELEASE(m_pGrid);
	OnDestructIScene();
}

void SceneTest::Init()
{
    //SkyBox* skyBox = new SkyBox;
    //D3DXMATRIXA16 tr;
    //const float scale = 20.0f;
    //D3DXMatrixScaling(&tr, scale, scale, scale);
    //skyBox->Init(&tr);
    //AddSimpleDisplayObj(skyBox);

	m_pGrid = new Grid; m_pGrid->Init();
	IDisplayObject* pObj = NULL;
	//pObj = new Frustum; pObj->Init(); AddSimpleDisplayObj(pObj);
	pObj = new ParticleTest; pObj->Init(); AddSimpleDisplayObj(pObj);
	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	//g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//g_pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//g_pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

    m_skinnedMesh = new SkinnedMesh;
    m_skinnedMesh->Init();
    AddSimpleDisplayObj(m_skinnedMesh);
}

void SceneTest::Update()
{
	OnUpdateIScene();
}

void SceneTest::Render()
{
	OnRenderIScene();
	SAFE_RENDER(m_pGrid);
}

void SceneTest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
