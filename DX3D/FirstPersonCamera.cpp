#include "stdafx.h"
#include "FirstPersonCamera.h"


FirstPersonCamera::FirstPersonCamera()
    :ICamera()
{
    m_cameraState = CameraState::FIRSTPERSON;
    m_distance = FP_DISTANCE;
    m_basePosX = FP_BASEPOSX;
    m_basePosY = FP_BASEPOSY;
    //70 Degrees FP sight
    m_fovY = D3DX_PI * (70.0f / 180.0f);
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::Init()
{
    ICamera::Init();
}

void FirstPersonCamera::Update()
{
    //RBUTTON Up 하면 다시 TP 로 돌아가기
    if(g_pKeyManager->IsOnceKeyUp(VK_RBUTTON))
        g_pCameraManager->SetCurrentCamera(CameraState::KYUNCHAK);
    ICamera::Update();
}

//---------------------------------------------------xx

Camera2xScope::Camera2xScope()
    :FirstPersonCamera()
    , m_currTime(0.0f)
    , m_totalTime(0.5f)
{
    m_cameraState = CameraState::SCOPE2X;
    //44.44 Degrees FP sight //선형보간할 것이다.
    m_fovY_2x = D3DX_PI * (44.44f / 180.0f);
}

Camera2xScope::~Camera2xScope()
{
}

void Camera2xScope::Init()
{
    m_currTime = 0.0f;
    m_deltaFovY = 0.0f;
    FirstPersonCamera::Init();
}

void Camera2xScope::Update()
{
    if (m_currTime <= m_totalTime)
    {
        const auto dt = g_pTimeManager->GetDeltaTime();
        m_currTime += dt;
        float timeFactor = m_currTime / m_totalTime;
        m_deltaFovY = m_fovY * (1.0f - timeFactor) + m_fovY_2x * timeFactor;
        D3DXMatrixPerspectiveFovLH(&m_matProj, m_deltaFovY, m_aspect, 1, 1000);
        g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
    }

    FirstPersonCamera::Update();
}



/*//보간
Position = PositionFrom*(1.0-time) + positionTo * time;//단 Time은 0~1 까지 (m_currTime / m_totalTime) 하고 m_currTime+=deltatime;
*/
//D3DXVec3Lerp(&pos, &m_from, &m_to, GetTimeRate());
//D3DXVec2Lerp(&m_accelarate, &D3DXVECTOR2(1.0f, 0.0f), &D3DXVECTOR2(0.0f, 0.0f), m_currTime / m_totalTime);
//Debug하기
//Debug->AddText("m_fovY : ");
//Debug->AddText(m_fovY);
//Debug->AddText("   m_fovY_2x : ");
//Debug->AddText(m_fovY_2x);
//Debug->AddText("   deltaFovY : ");
//Debug->AddText(m_deltaFovY);
//Debug->EndLine();
Camera4xScope::Camera4xScope()
    :FirstPersonCamera()
    , m_currTime(0.0f)
    , m_totalTime(0.5f)
{
    m_cameraState = CameraState::SCOPE4X;
    //44.44 Degrees FP sight //선형보간할 것이다.
    m_fovY_4x = D3DX_PI * (11.03f / 180.0f);
}

Camera4xScope::~Camera4xScope()
{
}

void Camera4xScope::Init()
{
    m_currTime = 0.0f;
    m_deltaFovY = 0.0f;
    FirstPersonCamera::Init();
}

void Camera4xScope::Update()
{
    if (m_currTime <= m_totalTime)
    {
        const auto dt = g_pTimeManager->GetDeltaTime();
        m_currTime += dt;
        float timeFactor = m_currTime / m_totalTime;
        m_deltaFovY = m_fovY * (1.0f - timeFactor) + m_fovY_4x * timeFactor;
        D3DXMatrixPerspectiveFovLH(&m_matProj, m_deltaFovY, m_aspect, 1, 1000);
        g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
    }

    FirstPersonCamera::Update();
}
