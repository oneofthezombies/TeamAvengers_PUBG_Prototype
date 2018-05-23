#include "stdafx.h"
#include "FirstPersonCamera.h"


FirstPersonCamera::FirstPersonCamera()
    :ICamera()
{
    m_cameraState = CameraState::FIRSTPERSON;
    m_distance = FP_DISTANCE;
    m_basePosX = 0;
    m_basePosY = 3;
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
