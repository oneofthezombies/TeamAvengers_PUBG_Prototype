#pragma once
#include "ICamera.h"
class FirstPersonCamera : public ICamera
{
public:
    FirstPersonCamera();
    virtual ~FirstPersonCamera();

    // Inherited via ICamera
    virtual void Init() override;
    virtual void Update() override;
};



class Camera2xScope
    : public FirstPersonCamera
{
private:
    float           m_fovY_2x;
    float           m_deltaFovY;
    
    float           m_currTime;
    const float     m_totalTime;
public:
    Camera2xScope();
    virtual ~Camera2xScope();

    // Inherited via ThirdPersonCamera
    virtual void Init() override;
    virtual void Update() override;

};


class Camera4xScope
    : public FirstPersonCamera
{
private:
    float           m_fovY_4x;
    float           m_deltaFovY;

    float           m_currTime;
    const float     m_totalTime;
public:
    Camera4xScope();
    virtual ~Camera4xScope();

    // Inherited via ThirdPersonCamera
    virtual void Init() override;
    virtual void Update() override;

};