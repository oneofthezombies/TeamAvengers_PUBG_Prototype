#include "stdafx.h"
#include "UIInGame.h"
#include "Gun.h"
#include "UIText.h"

UIInGame::UIInGame()
    : UIObject()
    , m_ppGun(nullptr)
{
}

UIInGame::~UIInGame()
{
}

void UIInGame::Init(Gun** ppGun, FIRE_MODE* pFireMode)
{
    m_ppGun = ppGun;

    UIText* numBullet = new UIText;
    numBullet->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageDescription));
    numBullet->SetSize(D3DXVECTOR2(200.0f, 50.0f));
    numBullet->SetPosition(D3DXVECTOR3(600.0f, 650.0f, 0.0f));
    numBullet->SetText(&m_numBulletText);
    AddChild(*numBullet);

    m_pFireMode = pFireMode;

    UIText* fireMode = new UIText;
    fireMode->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageDescription));
    fireMode->SetSize(D3DXVECTOR2(200.0f, 50.0f));
    fireMode->SetPosition(D3DXVECTOR3(600.0f, 600.0f, 0.0f));
    fireMode->SetText(&m_fireModeText);
    AddChild(*fireMode);
}

void UIInGame::Update()
{
    UpdateTextNumBullet();
    UpdateTextFireMode();
    UIObject::Update();
}

void UIInGame::UpdateTextNumBullet()
{
    if (m_ppGun)
    {
        if (*m_ppGun)
        {
            m_numBulletText = "현재 총알 개수 : " + to_string((*m_ppGun)->GetBulletNum()) + "/" + to_string((*m_ppGun)->GetMaxNumBullet());
            return;
        }
    }

    m_numBulletText = "";
}

void UIInGame::UpdateTextFireMode()
{
    if (m_pFireMode)
    {
        switch (*m_pFireMode)
        {
        case FIRE_MODE::SingleShot:
            {
                m_fireModeText = "단발 모드";
            }
            break;
        case FIRE_MODE::Burst:
            {
                m_fireModeText = "연발 모드";
            }
            break;
        }
        return;
    }

    m_fireModeText = "";
}

UIInGame* UIInGame::Create(Gun** ppGun, FIRE_MODE* pFireMode)
{
    UIInGame* ret = new UIInGame;
    ret->Init(ppGun, pFireMode);

    g_pUIManager->RegisterUIObject(*ret);

    return ret;
}
