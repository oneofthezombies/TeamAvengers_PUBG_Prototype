#pragma once

#include "BaseObject.h"

class CubemanAI
{
private:

public:
    CubemanAI();
    virtual ~CubemanAI();

    void Init();
    void Move(D3DXVECTOR3& OutDeltaPos, D3DXVECTOR3& OutDeltaRot, D3DXVECTOR3& OutMyRot, const D3DXVECTOR3& myPos);
};