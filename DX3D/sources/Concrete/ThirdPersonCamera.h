#pragma once
#include "ICamera.h"

class Ray;

class ThirdPersonCamera : public ICamera
{
private:
    Ray* m_pCamBackCheckingRay;

public:
    ThirdPersonCamera();
    virtual ~ThirdPersonCamera();

    // Inherited via ICamera
    virtual void Init() override;
    virtual void Update() override;

    void CamBackDistResizeing();

};


class CameraTPToFP
    : public ThirdPersonCamera
{
private:
    float m_vel;

public:
    CameraTPToFP();
    virtual ~CameraTPToFP();

    // Inherited via ThirdPersonCamera
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

    // Inherited via ThirdPersonCamera
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

    // Inherited via ThirdPersonCamera
    virtual void Init() override;
    virtual void Update() override;
};
