#include "stdafx.h"
#include "CubemanAI.h"
#include "PlayerAni.h"

CubemanAI::CubemanAI()
{
}

CubemanAI::~CubemanAI()
{
}

void CubemanAI::Init()
{
}

void CubemanAI::Move(D3DXVECTOR3& OutDeltaPos, D3DXVECTOR3& OutDeltaRot, D3DXVECTOR3& OutMyRot, const D3DXVECTOR3& myPos)
{
    ZeroMemory(&OutDeltaPos, sizeof OutDeltaPos);
    ZeroMemory(&OutDeltaRot, sizeof OutDeltaRot);

    IDisplayObject* search = g_pObjectManager->FindObjectByTag(TAG_PLAYER);
    if (!search) return;

    PlayerAni* player = static_cast<PlayerAni*>(search);
    const D3DXVECTOR3 playerPos = player->GetPosition();

    const D3DXVECTOR3 diff = D3DXVECTOR3(playerPos.x, 0.0f, playerPos.z) - D3DXVECTOR3(myPos.x, 0.0f, myPos.z);
    float diffLength = D3DXVec3Length(&diff);

    if (diffLength > 25.0f) return;

    const D3DXVECTOR3 diffNorm = diff / diffLength;

    D3DXMATRIX r;
    D3DXMatrixRotationY(&r, OutMyRot.y);
    D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
    D3DXVec3TransformNormal(&dir, &dir, &r);

    const float cosTheta = D3DXVec3Dot(&diffNorm, &dir);

    D3DXVECTOR3 yAxis;
    D3DXVec3Cross(&yAxis, &dir, &diffNorm);

    if (cosTheta > 0.95f)
    {
        OutDeltaPos.z = 1.0f;

        return;
    }
    else if (cosTheta > 0.8660 /* root 3 over 2 */)
    {
        if (yAxis.y < 0.0f)
            OutDeltaRot.y = -1.0f;

        else if (yAxis.y > 0.0f)
            OutDeltaRot.y = 1.0f;

        OutDeltaPos.z = 1.0f;

        return;
    }
    
    if (diffLength > 20.0f) return;

    if (yAxis.y < 0.0f)
        OutDeltaRot.y = -1.0f;

    else if (yAxis.y > 0.0f)
        OutDeltaRot.y = 1.0f;
}
