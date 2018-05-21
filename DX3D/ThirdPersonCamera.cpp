#include "stdafx.h"
#include "ThirdPersonCamera.h"


ThirdPersonCamera::ThirdPersonCamera()
{
    //잠시 temp 값을 넣은 것임, Charecter가 만들어지면 바꿀 것이다.
    m_cameraState = THIRDPERSON;
    m_distance = 5;
    m_basePosX = 2;
    m_basePosY = 5;
    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);
    m_lookAt = D3DXVECTOR3(0, 0, 0);
    m_up = D3DXVECTOR3(0, 1, 0);
    m_rotX = 0.0f;
    m_rotY = 0.0f;

    m_fovY = D3DX_PI / 2.0f;    //90Degrees 

    m_isLbuttonDown = false;
    m_isRbuttonDown = false;
}


ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::Init()
{
    D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
    g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

    RECT rc;
    GetClientRect(g_hWnd, &rc);

    D3DXMatrixPerspectiveFovLH(&m_matProj,
        m_fovY,
        rc.right / (float)rc.bottom, 1, 1000);
    g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

}

void ThirdPersonCamera::Update()
{
    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);

    D3DXMATRIXA16 matRotX, matRotY, matRot;
    D3DXMatrixRotationX(&matRotX, m_rotX);
    D3DXMatrixRotationY(&matRotY, m_rotY);
    matRot = matRotX * matRotY;

    D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);

    //if (m_pTarget)
    //{
    //    m_lookAt = *m_pTarget;
    //    m_eye = *m_pTarget + m_eye;
    //}

    D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
    g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

}
