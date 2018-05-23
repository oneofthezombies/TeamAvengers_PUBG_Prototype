#include "stdafx.h"
#include "ThirdPersonCamera.h"


ThirdPersonCamera::ThirdPersonCamera()
    :ICamera()
{
    m_cameraState = CameraState::THIRDPERSON;
    m_distance = TP_DISTANCE;
    m_basePosX = TP_BASEPOSX;
    m_basePosY = TP_BASEPOSY;
    m_fovY = D3DX_PI / 3.0f;    //60Degrees SS
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::Init()
{
    ICamera::Init();
}

void ThirdPersonCamera::Update()
{

    ICamera::Update();
}

//--------------------------------------------


CameraTPToFP::CameraTPToFP()
    : ThirdPersonCamera()
    , m_vel(0.0f)
{
    m_cameraState = CameraState::TP2FP;
}

CameraTPToFP::~CameraTPToFP()
{
}

void CameraTPToFP::Init()
{
    m_distance = TP_DISTANCE;
    m_vel = 0.0f;
    ThirdPersonCamera::Init();
}

void CameraTPToFP::Update()
{
    const auto dt = g_pTimeManager->GetDeltaTime();
    m_vel += dt*5.0f;
    m_distance -= m_vel * dt;
    if(m_distance <= TP_DISTANCE-1.0f)
        g_pCameraManager->SetCurrentCamera(CameraState::FIRSTPERSON);
    ThirdPersonCamera::Update();
}
CameraFPToTP::CameraFPToTP()
    : ThirdPersonCamera()
    , m_vel(0.0f)
{
    m_cameraState = CameraState::FP2TP;
}

CameraFPToTP::~CameraFPToTP()
{
}

void CameraFPToTP::Init()
{
    m_distance = TP_DISTANCE-1.0f;
    m_vel = 4.0f;
    ThirdPersonCamera::Init();
}

void CameraFPToTP::Update()
{
    const auto dt = g_pTimeManager->GetDeltaTime();
    m_vel -= dt * 5.0f;
    m_distance += m_vel * dt;
    if (m_distance>= TP_DISTANCE-0.01f)
        g_pCameraManager->SetCurrentCamera(CameraState::THIRDPERSON);
    
    ThirdPersonCamera::Update();
}

//--------------------------------------------

CameraKyunChak::CameraKyunChak()
    :ThirdPersonCamera()
    ,m_vel(0.0f)
{
}

CameraKyunChak::~CameraKyunChak()
{
}

void CameraKyunChak::Init()
{
    ThirdPersonCamera::Init();
    m_isLbuttonPressed = true;//Àá½Ã
}

void CameraKyunChak::Update()
{
    const auto dt = g_pTimeManager->GetDeltaTime();
    if (m_isLbuttonPressed)
    {
        if (m_distance >= TP_DISTANCE - 5.0f)
        {
            m_vel += dt * 5.0f;
            m_distance -= m_vel * dt;
            m_basePosY -= m_vel * dt *0.5f;
        }
    }
    else
    {
        m_vel -= dt * 5.0f;
        m_distance += m_vel * dt;
        m_basePosY += m_vel * dt;
        if (m_distance <= TP_DISTANCE-0.1f)
        {
            g_pCameraManager->SetCurrentCamera(CameraState::THIRDPERSON);
        }
    }
    if (GetAsyncKeyState('S') & 0x0001)
    {
        m_isLbuttonPressed = false;
    }

    ThirdPersonCamera::Update();
}

//Debug->AddText(dt);
//Debug->EndLine();
//m_currTime += dt;
//D3DXVec2Lerp(&m_accelarate, &D3DXVECTOR2(1.0f, 0.0f), &D3DXVECTOR2(0.0f, 0.0f), m_currTime / m_totalTime);
//if (m_accelarate.x <= 0.0f)
//    g_pCameraManager->SetCurrentCamera(CameraState::THIRDPERSON);
//    
//const float factor = 0.1f;
//m_vel += m_accelarate.x * factor;
//m_distance += m_vel * dt;