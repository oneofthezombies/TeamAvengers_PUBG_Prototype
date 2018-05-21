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

