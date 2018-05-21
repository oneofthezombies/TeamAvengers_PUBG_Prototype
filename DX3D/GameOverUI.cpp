#include "stdafx.h"
#include "GameOverUI.h"
#include "UIText.h"
#include "UIManager.h"
#include "UIButton.h"

GameOverUI::GameOverUI()
    : UIImage()
{
}

GameOverUI::~GameOverUI()
{
    SAFE_DELETE(m_listner);
}

void GameOverUI::Init()
{
    m_pTex = g_pTextureManager->GetTexture("resources/images/black_1280_720_70.png");
    m_size = D3DXVECTOR2(1280.0f, 720.0f);

    UIText* gameOverNickname = new UIText(g_pFontManager->GetFont(Font::kGameOverNickname));
    gameOverNickname->m_text = TEXT("oneofthezombies");
    gameOverNickname->m_color = D3DCOLOR_XRGB(255, 255, 255);
    gameOverNickname->SetPosition(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
    gameOverNickname->m_size = D3DXVECTOR2(500.0f, 50.0f);
    gameOverNickname->m_drawTextFormat = DT_LEFT;
    AddChild(*gameOverNickname);

    UIText* gameOverDescription = new UIText(g_pFontManager->GetFont(Font::kGameOverDescription));
    gameOverDescription->m_text = TEXT("ÀÌ°å´ß! ¿À´Ã Àú³áÀº Ä¡Å²ÀÌ´ß!");
    gameOverDescription->m_color = D3DCOLOR_XRGB(242, 199, 35);
    gameOverDescription->SetPosition(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
    gameOverDescription->m_size = D3DXVECTOR2(500.0f, 50.0f);
    gameOverDescription->m_drawTextFormat = DT_LEFT;
    gameOverNickname->AddChild(*gameOverDescription);

    UIText* gameOverRanking = new UIText(g_pFontManager->GetFont(Font::kGameOverRanking));
    gameOverRanking->m_text = TEXT("#1");
    gameOverRanking->m_color = D3DCOLOR_XRGB(242, 199, 35);
    gameOverRanking->SetPosition(D3DXVECTOR3(1280.0f - 200.0f, 50.0f, 0.0f));
    gameOverRanking->m_size = D3DXVECTOR2(80.0f, 50.0f);
    gameOverRanking->m_drawTextFormat = DT_RIGHT;
    AddChild(*gameOverRanking);

    UIText* gameOverRankingNumOther = new UIText(g_pFontManager->GetFont(Font::kGameOverRankingNumOther));
    gameOverRankingNumOther->m_text = TEXT("/50");
    gameOverRankingNumOther->m_color = D3DCOLOR_XRGB(90, 94, 97);
    gameOverRankingNumOther->SetPosition(D3DXVECTOR3(80.0f, 8.0f, 0.0f));
    gameOverRankingNumOther->m_size = D3DXVECTOR2(80.0f, 50.0f);
    gameOverRankingNumOther->m_drawTextFormat = DT_LEFT;
    gameOverRanking->AddChild(*gameOverRankingNumOther);

    m_listner = new IUIButtonListner;
    m_listner->m_pAttached = this;
    UIButton* gameOverGoToLobby = new UIButton(m_listner, m_listner);
    gameOverGoToLobby->m_size = D3DXVECTOR2(200.0f, 80.0f);
    gameOverGoToLobby->SetPosition(D3DXVECTOR3(1280.0f - 300.0f, 720.0f - 150.0f, 0.0f));
    AddChild(*gameOverGoToLobby);

    UIText* gameOverGoToLobbyText = new UIText(g_pFontManager->GetFont(Font::kGameOverGoToLobby));
    gameOverGoToLobbyText->m_size = D3DXVECTOR2(200.0f, 60.0f);
    gameOverGoToLobbyText->SetPosition(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
    gameOverGoToLobbyText->m_text = TEXT("·Îºñ·Î ³ª°¡±â");
    gameOverGoToLobbyText->m_color = D3DCOLOR_XRGB(93, 93, 93);
    gameOverGoToLobby->AddChild(*gameOverGoToLobbyText);
}

void IUIButtonListner::OnMouseEnter()
{
}

void IUIButtonListner::OnMouseExit()
{
}

void IUIButtonListner::OnMouseDown(const MouseButton::Type button)
{
    g_pUIManager->Destroy(*m_pAttached);
}

void IUIButtonListner::OnMouseUp(const MouseButton::Type button)
{
}

void IUIButtonListner::OnMouseDrag(const MouseButton::Type button)
{
}
