#include "stdafx.h"
#include "ICamera.h"

ICamera::ICamera()
    : m_rotX(0.0f)
    , m_rotY(0.0f)
{
    RECT rc;
    GetClientRect(g_hWnd, &rc);
    m_aspect = rc.right / (float)rc.bottom;
}

void ICamera::Init()
{
    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);

    D3DXVECTOR3* pTargetDir;
    UpdateEye();

    m_lookAt = D3DXVECTOR3(m_eye.x, m_eye.y, m_eye.z + 1);
    m_up = D3DXVECTOR3(0, 1, 0);

    //m_ptPrevMouse;
    D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
    g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

    D3DXMatrixPerspectiveFovLH(&m_matProj,m_fovY,m_aspect, 1, 1000);
    g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void ICamera::Update()
{
    Debug->AddText(m_distance);
    Debug->AddText(m_basePosX);
    Debug->AddText(m_basePosY);
    Debug->EndLine();

    //    
    //if (g_pKeyManager->IsOnceKeyDown('J'))
    //    m_aspect -= 0.01f;//m_aspect
    //if (g_pKeyManager->IsOnceKeyDown('N'))
    //    m_aspect += 0.01f;//m_aspect

    //D3DXMatrixPerspectiveFovLH(&m_matProj, m_fovY, m_aspect, 1, 1000);
    //g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
    //start

    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);
    UpdateEye();

    //Player가 움직여도 계속 앞을 보게 하려면 1
    m_lookAt = D3DXVECTOR3(m_eye.x, m_eye.y-0.1, m_eye.z + 1);

    D3DXMATRIXA16 matRot;
    D3DXMatrixRotationYawPitchRoll(&matRot, m_rotY, m_rotX, 0.0f);

    D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);
    //Player가 움직여도 계속 앞을 보게 하려면 2
    D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &matRot);

    D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
    g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

}

void ICamera::UpdateEye()
{
    if (D3DXVECTOR3* pTargetPos = g_pCameraManager->GetTargetPos())
        m_eye += *pTargetPos;
}

