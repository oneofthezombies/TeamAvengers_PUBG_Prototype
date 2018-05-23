#pragma once
#include "ICamera.h"
class ThirdPersonCamera : public ICamera
{
public:
    ThirdPersonCamera();
    virtual ~ThirdPersonCamera();

    // Inherited via ICamera
    virtual void Init() override;
    virtual void Update() override;
};


class CameraTPToFP
    : public ThirdPersonCamera
{
private:
    float m_vel;

public:
    CameraTPToFP();
    virtual ~CameraTPToFP();

    // Inherited via ICamera
    virtual void Init() override;
    virtual void Update() override;
};


class CameraFPToTP
    : public ThirdPersonCamera
{
private:
    float m_vel;

public:
    CameraFPToTP();
    virtual ~CameraFPToTP();

    // Inherited via ICamera
    virtual void Init() override;
    virtual void Update() override;
};


class CameraKyunChak
    : public ThirdPersonCamera
{
private:
    float           m_vel;

public:
    CameraKyunChak();
    virtual ~CameraKyunChak();


    virtual void Init() override;
    virtual void Update() override;
};
