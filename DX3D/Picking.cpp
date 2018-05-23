#include "stdafx.h"
#include "Picking.h"
#include "Ray.h"

Picking::Picking()
{
	m_pSphere = NULL;
}


Picking::~Picking()
{
	SAFE_RELEASE(m_pSphere);
	for (auto p : m_vecBoundary)
		SAFE_DELETE(p);
}

void Picking::Init()
{
	int dim = 7;
	float radius = 0.2f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);

	m_vecBoundary.reserve(dim * dim * dim);
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				BoundingSphere* s = new BoundingSphere(
					D3DXVECTOR3(i + 5, j + 5, k + 5), radius);
				m_vecBoundary.push_back(s);
			}
		}
	}
}

void Picking::Update()
{
}

void Picking::Render()
{
	
	for (auto p : m_vecBoundary)
	{
		//if (!g_pCamera->CheckSphere(p))
		//	continue;
		if (p->isPicked == true)
		{
			g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
		}
		else
		{
			g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
		}
		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, p->center.x, p->center.y, p->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphere->DrawSubset(0);
	}
}

void Picking::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONUP:
	{
		Ray r = Ray::RayAtWorldSpace(SCREEN_POINT(lParam));
		for (auto p : m_vecBoundary)
		{
			//p->isPicked = r.CalcIntersectSphere(p);
		}
		BoundingSphere* sphere = NULL;
		float minDistance = FLT_MAX;
		float intersectionDistance;
		for (auto p : m_vecBoundary)
		{
			p->isPicked = false;
			if (r.CalcIntersectSphere(p) == true)
			{
				intersectionDistance =
					D3DXVec3Length(&(p->center - r.m_pos));
				if (intersectionDistance < minDistance)
				{
					minDistance = intersectionDistance;
					sphere = p;
				}
			}
		}
		if (sphere != NULL)
		{
			sphere->isPicked = true;
		}

	}
	break;
	default:
		break;
	}
}
