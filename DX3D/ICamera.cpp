#include "stdafx.h"
#include "ICamera.h"

ICamera::ICamera()
    : m_rotX(0.0f)
    , m_rotY(0.0f)
{
    RECT rc;
    GetClientRect(g_hWnd, &rc);
    m_aspect = rc.right / (float)rc.bottom;
    m_up = D3DXVECTOR3(0, 1, 0);
}

void ICamera::Init()
{
    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);
    m_lookAt = D3DXVECTOR3(m_eye.x, m_eye.y, m_eye.z+1);

    //m_ptPrevMouse;
    D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
    g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

    D3DXMatrixPerspectiveFovLH(&m_matProj,m_fovY,m_aspect, 1, 1000);
    g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void ICamera::Update()
{
    D3DXMATRIXA16 matWorld;
    D3DXMatrixIdentity(&matWorld);

    D3DXVECTOR3* pTargetPos = g_pCameraManager->GetTargetPos();
    D3DXVECTOR3* pTargetRot = g_pCameraManager->GetTargetDir();

    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);
    m_lookAt = D3DXVECTOR3(m_eye.x, m_eye.y, m_eye.z + 1);

    D3DXMATRIXA16 matR, matT;
    D3DXMatrixRotationYawPitchRoll(&matR, pTargetRot->y, pTargetRot->x, pTargetRot->z);
    
    D3DXMatrixTranslation(&matT, pTargetPos->x, pTargetPos->y, pTargetPos->z);
    matWorld = matWorld *matR* matT;
    D3DXVec3TransformCoord(&m_eye, &m_eye, &matWorld);
    D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &matWorld);
    
    
    
    
    



    //D3DXMATRIXA16 matRot;
    //D3DXMatrixRotationYawPitchRoll(&matRot, m_rotY, m_rotX, 0.0f);

    //D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);
    ////Player가 움직여도 계속 앞을 보게 하려면 2
    //D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &matRot);

    D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
    g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

}

void ICamera::UpdateEye()
{
    D3DXVECTOR3* pTargetPos = g_pCameraManager->GetTargetPos();
    D3DXVECTOR3* pTargetDir = g_pCameraManager->GetTargetDir();

    if (!pTargetPos || !pTargetDir) return;

    Debug->AddText("target pos : ");
    Debug->AddText(*pTargetPos);
    Debug->EndLine();
    Debug->AddText("target dir : ");
    Debug->AddText(*pTargetDir);
    Debug->EndLine();

    auto rev = *pTargetDir * -m_distance;
    m_eye = *pTargetPos + rev;
    D3DXVECTOR3 v;
    D3DXMATRIXA16 m;
    D3DXMatrixRotationY(&m, D3DX_PI * 0.5f);
    v = *pTargetDir;
    D3DXVec3TransformNormal(&v, &v, &m);
    m_eye += v * m_basePosX;
    D3DXMatrixRotationX(&m, D3DX_PI * -0.5f);
    v = *pTargetDir;
    D3DXVec3TransformCoord(&v, &v, &m);
    m_eye += v * m_basePosY;
    m_lookAt = *pTargetPos + *pTargetDir * 100.0f;
}

