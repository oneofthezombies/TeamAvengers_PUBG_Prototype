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

void UIInGame::Init(Gun** ppGun)
{
    m_ppGun = ppGun;

    UIText* numBullet = new UIText;
    numBullet->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageDescription));
    numBullet->SetSize(D3DXVECTOR2(200.0f, 50.0f));
    numBullet->SetPosition(D3DXVECTOR3(600.0f, 650.0f, 0.0f));
    numBullet->SetText(&m_numBulletText);
    AddChild(*numBullet);
}

void UIInGame::Update()
{
    UpdateTextNumBullet();
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

UIInGame* UIInGame::Create(Gun** ppGun)
{
    UIInGame* ret = new UIInGame;
    ret->Init(ppGun);

    g_pUIManager->RegisterUIObject(*ret);

    return ret;
}
