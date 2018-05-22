#include "stdafx.h"
#include "SampleCollidable.h"

void CollidablePlayerBox::Init()
{
    BoxCollider* bc = new BoxCollider;
    bc->Init(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f));
    m_pCollider = bc;
}

void CollidablePlayerBox::Update()
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    BoxCollider* bc = static_cast<BoxCollider*>(m_pCollider);
    D3DXMATRIXA16 tr;
    float trX = 0.0f;
    if (GetKeyState(VK_LEFT) & 0x8000)
    {
        trX -= 0.01f;
    }

    if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        trX += 0.01f;
    }

    D3DXMatrixTranslation(&tr, trX, 0.0f, 0.0f);
    bc->Update(&tr);
}

void CollidablePlayerBox::OnCollision(ICollidable& other)
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));
}

void CollidableItemBox::Init()
{
    BoxCollider* bc = new BoxCollider;
    bc->Init(D3DXVECTOR3(-0.5f, -2.0f, -1.0f), D3DXVECTOR3(0.5f, 2.0f, 1.0f));
    m_pCollider = bc;
}

void CollidableItemBox::Update()
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(0, 255, 0));

    BoxCollider* bc = static_cast<BoxCollider*>(m_pCollider);
    D3DXMATRIXA16 tr;
    float rotY = 0.0f;
    float rotX = 0.0f;

    if (GetKeyState('W') & 0x8000)
    {
        rotX += 0.01f;
    }

    if (GetKeyState('S') & 0x8000)
    {
        rotX -= 0.01f;
    }

    if (GetKeyState('A') & 0x8000)
    {
        rotY -= 0.01f;
    }

    if (GetKeyState('D') & 0x8000)
    {
        rotY += 0.01f;
    }

    D3DXMatrixRotationYawPitchRoll(&tr, rotY, 0.0f, rotX);

    bc->Update(&tr);
}

void CollidableItemBox::OnCollision(ICollidable& other)
{
    if (m_pCollider)
        m_pCollider->SetColor(D3DCOLOR_XRGB(255, 0, 0));
}
