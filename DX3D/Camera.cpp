#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	m_distance = 10.0f;
	m_basePosY = 5.0f;
	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);
	m_lookAt = D3DXVECTOR3(0, 0, 0);
	m_up = D3DXVECTOR3(0, 1, 0);
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_isLbuttonDown = false;
	m_pTarget = NULL;

	SetProjVert();
	ChangeToWorldVert();
	SetSixPlane();
}


Camera::~Camera()
{
}

void Camera::Init()
{
	D3DXMatrixLookAtLH(&m_matView,
		&m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMatrixPerspectiveFovLH(&m_matProj,
		D3DX_PI / 4.0f,
		rc.right / (float)rc.bottom, 1, 1000);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void Camera::Update()
{
	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);

	D3DXMATRIXA16 matRotX, matRotY, matRot;
	D3DXMatrixRotationX(&matRotX, m_rotX);
	D3DXMatrixRotationY(&matRotY, m_rotY);
	matRot = matRotX * matRotY;

	D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);

	if (m_pTarget)
	{
		m_lookAt = *m_pTarget;
		m_eye = *m_pTarget + m_eye;
	}

	D3DXMatrixLookAtLH(&m_matView,
		&m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	if (GetAsyncKeyState('1') & 0x0001)
	{
		ChangeToWorldVert();
		SetSixPlane();
	}
}

void Camera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLbuttonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLbuttonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (m_isLbuttonDown == true)
		{
			POINT currPoint;
			currPoint.x = LOWORD(lParam);
			currPoint.y = HIWORD(lParam);

			m_rotY += (currPoint.x - m_ptPrevMouse.x) / 100.0f;
			m_rotX += (currPoint.y - m_ptPrevMouse.y) / 100.0f;

			if (m_rotX <= -D3DX_PI * 0.5f + D3DX_16F_EPSILON)
			{
				m_rotX = -D3DX_PI * 0.5f + D3DX_16F_EPSILON;
			}
			if (m_rotX >= D3DX_PI * 0.3f - D3DX_16F_EPSILON)
			{
				m_rotX = D3DX_PI * 0.3f - D3DX_16F_EPSILON;
			}

			m_ptPrevMouse = currPoint;
		}
	}
	break;
	case WM_MOUSEWHEEL:
		m_distance -= GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
		if (m_distance <= 10) m_distance = 10;
		if (m_distance >= 30) m_distance = 30;
		break;
	}
}
//D3DXVec3Unproject(out v3,in v3,viewport,projection,view,world) //한번에 viewport에서 local로 
//D3DXPlaneFromPoints(out plane, v1, v2, v3);
//D3DXPlaneDotCoord	//a b c d 내적 x y z 1
//결과값이 0보다 크면 안그려주면 된다 
//put 반지름 거리까지 신경쓸 것이니, D3DXPlaneDotCoord(plane, sphere0>center) -radius>0 을 해서 계산
void Camera::SetProjVert()
{
	m_vecProjVert.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjVert.push_back(D3DXVECTOR3(-1, 1, 0));
	m_vecProjVert.push_back(D3DXVECTOR3(1, 1, 0));
	m_vecProjVert.push_back(D3DXVECTOR3(1, -1, 0));
	m_vecProjVert.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjVert.push_back(D3DXVECTOR3(-1, 1, 1));
	m_vecProjVert.push_back(D3DXVECTOR3(1, 1, 1));
	m_vecProjVert.push_back(D3DXVECTOR3(1, -1, 1));
}

void Camera::ChangeToWorldVert()
{
	m_vecWorldVert.resize(m_vecProjVert.size());
	for (int i = 0; i < m_vecProjVert.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVert[i], &m_vecProjVert[i], NULL, &m_matProj, &m_matView, NULL);
	}
}

void Camera::SetSixPlane()
{
	m_vecSixPlane.resize(6);

	D3DXPlaneFromPoints(&m_vecSixPlane[0], &m_vecWorldVert[0], &m_vecWorldVert[1], &m_vecWorldVert[2]);
	D3DXPlaneFromPoints(&m_vecSixPlane[1], &m_vecWorldVert[3], &m_vecWorldVert[2], &m_vecWorldVert[6]);
	D3DXPlaneFromPoints(&m_vecSixPlane[2], &m_vecWorldVert[4], &m_vecWorldVert[5], &m_vecWorldVert[1]);
	D3DXPlaneFromPoints(&m_vecSixPlane[3], &m_vecWorldVert[7], &m_vecWorldVert[6], &m_vecWorldVert[5]);
	D3DXPlaneFromPoints(&m_vecSixPlane[4], &m_vecWorldVert[1], &m_vecWorldVert[5], &m_vecWorldVert[6]);
	D3DXPlaneFromPoints(&m_vecSixPlane[5], &m_vecWorldVert[4], &m_vecWorldVert[0], &m_vecWorldVert[3]);

}

bool Camera::CheckSphere(BoundingSphere * sphere)
{
	for (int i = 0; i < 6; i++)
	{
		if ((D3DXPlaneDotCoord(&m_vecSixPlane[i], &sphere->center) - sphere->radius)>0)
			return false;
	}
	
	return true;
}
