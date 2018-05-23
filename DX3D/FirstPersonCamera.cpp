#include "stdafx.h"
#include "FirstPersonCamera.h"


FirstPersonCamera::FirstPersonCamera()
    :ICamera()
{
    m_cameraState = CameraState::FIRSTPERSON;
    m_distance = FP_DISTANCE;
    m_basePosX = FP_BASEPOSX;
    m_basePosY = FP_BASEPOSY;
    m_fovY = D3DX_PI / 4.0f;    //45Degrees sight
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
    ICamera::Update();
}
