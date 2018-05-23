#include "stdafx.h"
#include "PlayerAni.h"
#include "PlayerParts.h"
#include "KeyManager.h"

enum enumParts
{
    head,
    left,
    right,
    leftleg,
    rightleg
};



PlayerAni::PlayerAni()
{
    m_pRootParts = NULL;

    m_isMoving = false;
    m_moveSpeed = 0.2f;
    m_currMoveSpeedRate = 1.0f;
    m_rotationSpeed = 0.1f;

    m_isJumping = false;
    m_jumpPower = 1.0f;
    m_gravity = 0.05f;
    m_currGravity = 0.0f;

    m_maxStepHeight = 2.0f;

    m_isRunnig = false;
    m_isLive = true;
}


PlayerAni::~PlayerAni()
{
    m_pRootParts->ReleaseAll();
}

void PlayerAni::Init()
{
    g_pObjMgr->AddToTagList(TAG_PLAYER, this);
    g_pCamera->SetTarget(&m_pos);
    CreateAllParts();
    
}

void PlayerAni::Update()
{

    if (g_pKeyManager->IsStayKeyDown('A'))
    {
        m_deltaRot = D3DXVECTOR3(0,-1,0);
       
    }
    else if(g_pKeyManager->IsStayKeyDown('D'))
    {
        m_deltaRot = D3DXVECTOR3(0, 1, 0);
    }
    else
    {
        m_deltaRot = D3DXVECTOR3(0, 0, 0);
    }

    if (g_pKeyManager->IsStayKeyDown('W'))
    {
        m_deltaPos.z = 1;
    }
    else if (g_pKeyManager->IsStayKeyDown('S'))
    {
        m_deltaPos.z = -1;

    }
    else
    {
        m_deltaPos.z = 0;

    }

    if(g_pKeyManager->IsOnceKeyDown(VK_SPACE))
    {
        m_isJumping = true;
    }


    //¶Ù°í °È±â
    RunAndWalk();

    if (g_pKeyManager->IsOnceKeyDown('F'))
    {
        //ÃÑ ³Ö°í »©±â
        DrawGunInOut();
    }
    
    if (g_pKeyManager->IsOnceKeyDown('G'))
    {
        DiedAni();
    }


    if (m_isLive)
    {
        UpdatePosition();
    }

   

    Debug->AddText("test : ");
    Debug->AddText(m_rot.x);
    Debug->EndLine();

    

    m_pRootParts->SetMovingState(m_isMoving);
    m_pRootParts->Update();
}

void PlayerAni::Render()
{
    g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
    m_pRootParts->Render();
}

void PlayerAni::UpdatePosition()
{
    m_rot += m_deltaRot * m_rotationSpeed;
    D3DXMATRIXA16 matRotY;

    if (m_isLive)
    {
        D3DXMatrixRotationY(&matRotY, m_rot.y);
        D3DXVec3TransformNormal(&m_forward,
            &D3DXVECTOR3(0, 0, 1), &matRotY);
    }
    else
    {
        D3DXMatrixRotationX(&matRotY, m_rot.x);
        D3DXVec3TransformNormal(&m_forward,
            &D3DXVECTOR3(0, 0, 1), &matRotY);
    }


    D3DXVECTOR3 targetPos;
    float basePosY = 0;
    bool	isIntersected = true;
    float	height = 0;

    if (m_isJumping == true)
    {
        m_currMoveSpeedRate = 0.7f;
        targetPos = m_pos + m_forward * m_deltaPos.z
            * m_moveSpeed * m_currMoveSpeedRate;

        targetPos.y += m_jumpPower - m_currGravity;
        m_currGravity += m_gravity;

        if (g_pCurrentMap != NULL)
        {
            isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
        }

        if (isIntersected == false)
        {
            if (g_pCurrentMap != NULL)
            {
                isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
            }
            m_pos.y = targetPos.y;
        }
        else
        {
            m_pos = targetPos;
        }

        if (m_pos.y <= height && m_jumpPower < m_currGravity)
        {
            m_pos.y = height;
            m_isJumping = false;
            m_currGravity = 0;
            m_currMoveSpeedRate = 1.0f;
        }
        //m_pos = targetPos;
    }
    else //m_isJumping == false
    {
        targetPos = m_pos + m_forward * m_deltaPos.z
            * m_moveSpeed * m_currMoveSpeedRate;

        if (g_pCurrentMap != NULL)
        {
            isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
            int tmp = 0;
            if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
            {

            }
            else
            {
                targetPos.y = height;
                m_pos = targetPos;
            }
        }
        else
        {
            m_pos = targetPos;
        }

        //m_pos = targetPos;
    }

    D3DXMATRIXA16 matT;
    D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
    m_matWorld = matRotY * matT;

    if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON ||
        D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
        m_isMoving = true;
    else
        m_isMoving = false;
}

void PlayerAni::CreateAllParts()
{
    PlayerParts* pParts;
    //¸öÅë
    m_pRootParts = new PlayerParts();
    CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),
        D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody, tEmpty);
    //¸Ó¸®
    pParts = new PlayerParts();
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
        D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead, tEmpty);
    //¿ÞÆÈ
    pParts = new PlayerParts(0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm, tEmpty);
    //¿À¸¥ÆÈ
    pParts = new PlayerParts(-0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm, tEmpty);
    //¿Þ´Ù¸®
    pParts = new PlayerParts(-0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg, tEmpty);
    //¿À¸¥´Ù¸®
    pParts = new PlayerParts(0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg, tEmpty);
}

void PlayerAni::CreateParts(PlayerParts *& pParts, IDisplayObject * pParent, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans, vector<vector<int>>& vecUV, PartTag tag)
{
    D3DXMATRIXA16 matS, matT, mat;
    D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
    D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
    mat = matS * matT;
    pParts->Init(&mat, vecUV);
    pParts->SetPosition(&pos);
    pParts->SetPartTag(tag);
    pParent->AddChild(pParts);

}

void PlayerAni::DrawGunInOut()
{
    PartTag tag = GetChild(right)->GetPartTag();
    float tem_rotX = GetChild(left)->GetRotXspeed();

    if (tag != tEmpty)
    {
        GetChild(right)->SetPartTag(tEmpty);
        GetChild(right)->SetRotXspeed(-1 * tem_rotX);
        GetChild(right)->SyncMotion();
    }
    else
    {
        GetChild(right)->SetPartTag(tGun);
    }
}

void PlayerAni::RunAndWalk()
{
    if (g_pKeyManager->IsStayKeyDown(VK_LSHIFT))
    {
        if (m_isRunnig == false)
        {
            m_moveSpeed = 0.35;
            for (int i = 1; i < m_pRootParts->GetChildVec().size(); i++)
            {
                GetChild(i)->SetRotXspeed(GetChild(i)->GetRotXspeed() * 1.5f);
            }
            m_isRunnig = true;
        }
    }
    else
    {
        if (m_isRunnig == true)
        {
            m_moveSpeed = 0.2f;
            for (int i = 1; i < m_pRootParts->GetChildVec().size(); i++)
            {
                GetChild(i)->SetRotXspeed(GetChild(i)->GetRotXspeed()/ 1.5f);
            }
            m_isRunnig = false;
        }
    }
}

void PlayerAni::DiedAni()
{
    if (m_isLive == true)
    {
        m_isLive = false;
        m_rot.x = D3DX_PI / 2.1f;
        UpdatePosition();
        m_isMoving = false;
    }
}


