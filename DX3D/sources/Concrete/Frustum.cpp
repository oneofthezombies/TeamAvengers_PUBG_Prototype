#include "stdafx.h"
#include "Frustum.h"


Frustum::Frustum()
{
}


Frustum::~Frustum()
{
	SAFE_RELEASE(m_pMesh);
}

void Frustum::Init()
{
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 1));
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 1));
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 0));
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 0));
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 1));
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 0));

	m_vecWorldVtx.resize(8);
	m_vecPlane.resize(6);

	// 구체 그려주기 dim*dim*dim
	int dim = 6;
	float offset = 4;
	float half = (dim - 1)*offset / 2.0f;
	float radius = 0.6f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pMesh, NULL);

	m_vecpBoundary.reserve(dim * dim * dim);
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				BoundingSphere* s = new BoundingSphere(
					D3DXVECTOR3(i*offset - half, j *offset - half, k*offset - half), radius);
				m_vecpBoundary.push_back(s);
			}
		}
	}
	UpdateFrustum();
}

void Frustum::Update()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		UpdateFrustum();
	}
}

void Frustum::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetMaterial(&DXUtil::BLUE_MTRL);
	g_pDevice->SetTexture(0, NULL);

	for (auto p : m_vecpBoundary)
	{
		if (IsSphereInsideFrustum(p) == true)
		{
			D3DXMATRIX mat;
			D3DXMatrixTranslation(&mat, p->center.x, p->center.y, p->center.z);
			g_pDevice->SetTransform(D3DTS_WORLD, &mat);
			m_pMesh->DrawSubset(0);
		}
	}
}

void Frustum::UpdateFrustum()
{
	D3DXMATRIX matProj, matView;
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pDevice->GetTransform(D3DTS_VIEW, &matView);

	for (size_t i = 0; i < m_vecWorldVtx.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVtx[i], &m_vecProjVtx[i], NULL, &matProj, &matView, NULL);
	}

	//6개의 면을 만드는 부분
	//전평면
	D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecWorldVtx[2], &m_vecWorldVtx[3], &m_vecWorldVtx[6]);
	//후평면
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVtx[1], &m_vecWorldVtx[0], &m_vecWorldVtx[5]);
	//좌평면
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVtx[0], &m_vecWorldVtx[2], &m_vecWorldVtx[4]);
	//우평면
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVtx[3], &m_vecWorldVtx[1], &m_vecWorldVtx[7]);
	//상평면
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVtx[0], &m_vecWorldVtx[1], &m_vecWorldVtx[2]);
	//하평면
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVtx[6], &m_vecWorldVtx[7], &m_vecWorldVtx[4]);
}


bool Frustum::IsSphereInsideFrustum(BoundingSphere * pSphere)
{
	// sphere 이 절두체 밖에 있으면 안그리면 된다.
	for (auto p : m_vecPlane)
	{
		if (D3DXPlaneDotCoord(&p, &pSphere->center) > pSphere->radius)
		{
			//center가 면의 앞쪽에 위치하고 
			//center 와 면의 거리가 radius 보다 크다
			return false;
		}
	}
	return true;
}
