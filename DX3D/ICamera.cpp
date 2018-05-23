#include "stdafx.h"
#include "ICamera.h"

ICamera::ICamera()
{
    RECT rc;
    GetClientRect(g_hWnd, &rc);
    m_aspect = rc.right / (float)rc.bottom;
}

void ICamera::Init()
{
    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);
    m_lookAt = D3DXVECTOR3(m_eye.x, m_eye.y, m_eye.z + 1);
    m_up = D3DXVECTOR3(0, 1, 0);
    m_rotX = 0.0f;
    m_rotY = 0.0f;
    m_isLbuttonDown = false;
    m_isLbuttonPressed = false;
    m_isLbuttonUp = false;
    m_isRbuttonDown = false;
    m_isALTbuttonDown = false;
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

    //잠시 temp key
    if (GetAsyncKeyState('Z') & 0x0001)
        m_isALTbuttonDown = true;

        
    //if (GetAsyncKeyState('C') & 0x0001)
    //    m_fovY -= 0.01f;//m_aspect
    //if (GetAsyncKeyState('X') & 0x0001)
    //    m_fovY += 0.01f;//m_aspect

    m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);
    //Player가 움직여도 계속 앞을 보게 하려면 1
    m_lookAt = D3DXVECTOR3(m_eye.x, m_eye.y-0.1, m_eye.z + 1);

    D3DXMATRIXA16 matRotX, matRotY, matRot;
    D3DXMatrixRotationX(&matRotX, m_rotX);
    D3DXMatrixRotationY(&matRotY, m_rotY);
    matRot = matRotX * matRotY;

    D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);
    //Player가 움직여도 계속 앞을 보게 하려면 2
    D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &matRot);

    D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
    g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

}

void ICamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_MOUSEMOVE:
    {
        if (m_isALTbuttonDown == true)
        {
            POINT currPoint;
            currPoint.x = LOWORD(lParam);
            currPoint.y = HIWORD(lParam);

            m_rotY += (currPoint.x - m_ptPrevMouse.x) / 500.0f;
            m_rotX += (currPoint.y - m_ptPrevMouse.y) / 500.0f;

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
    }
    //case WM_MOUSEWHEEL:
    //    m_distance -= GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
    //    if (m_distance <= 10) m_distance = 10;
    //    if (m_distance >= 30) m_distance = 30;
    //    break;
    //}
}
