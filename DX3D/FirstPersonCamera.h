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

