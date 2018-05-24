#include "stdafx.h"
#include "UIGameOver.h"
#include "UIText.h"
#include "UIManager.h"
#include "UIButton.h"

UIGameOver::UIGameOver()
    : UIImage()
    , m_pGoToLobbyButtonListener(nullptr)
{
}

UIGameOver::~UIGameOver()
{
    SAFE_DELETE(m_pGoToLobbyButtonListener);
}

void UIGameOver::Init()
{
    g_pUIManager->RegisterUIObject(*this);

    SetTexture("resources/images/black_1280_720_70.png");
    SetSize(D3DXVECTOR2(1280.0f, 720.f));

    UIText* nickname = new UIText;
    nickname->SetFont(g_pFontManager->GetFont(Font::kGameOverNickname));
    nickname->SetText(TEXT("oneofthezombies"));
    nickname->SetColor(D3DCOLOR_XRGB(255, 255, 255));
    nickname->SetPosition(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
    nickname->SetSize(D3DXVECTOR2(500.0f, 50.0f));
    nickname->SetDrawTextFormat(DT_LEFT);
    AddChild(*nickname);

    UIText* description = new UIText;
    description->SetFont(g_pFontManager->GetFont(Font::kGameOverDescription));
    description->SetText(TEXT("ÀÌ°å´ß! ¿À´Ã Àú³áÀº Ä¡Å²ÀÌ´ß!"));
    description->SetColor(D3DCOLOR_XRGB(242, 199, 35));
    description->SetPosition(D3DXVECTOR3(0.0f, 60.0f, 0.0f));
    description->SetSize(D3DXVECTOR2(500.0f, 50.0f));
    description->SetDrawTextFormat(DT_LEFT);
    nickname->AddChild(*description);

    UIText* ranking = new UIText;
    ranking->SetFont(g_pFontManager->GetFont(Font::kGameOverRanking));
    ranking->SetText(TEXT("#1"));
    ranking->SetColor(D3DCOLOR_XRGB(242, 199, 35));
    ranking->SetPosition(D3DXVECTOR3(1280.0f - 200.0f, 50.0f, 0.0f));
    ranking->SetSize(D3DXVECTOR2(80.0f, 50.0f));
    ranking->SetDrawTextFormat(DT_RIGHT);
    AddChild(*ranking);

    UIText* rankingNumOther = new UIText;
    rankingNumOther->SetFont(g_pFontManager->GetFont(Font::kGameOverRankingNumOther));
    rankingNumOther->SetText(TEXT("/50"));
    rankingNumOther->SetColor(D3DCOLOR_XRGB(90, 94, 97));
    rankingNumOther->SetPosition(D3DXVECTOR3(80.0f, 8.0f, 0.0f));
    rankingNumOther->SetSize(D3DXVECTOR2(80.0f, 50.0f));
    rankingNumOther->SetDrawTextFormat(DT_LEFT);
    ranking->AddChild(*rankingNumOther);

    UIButton* goToLobby = new UIButton;
    goToLobby->SetSize(D3DXVECTOR2(200.0f, 80.0f));
    goToLobby->SetPosition(D3DXVECTOR3(1280.0f - 300.0f, 720.0f - 150.0f, 0.0f));
    AddChild(*goToLobby);
    m_pGoToLobbyButtonListener = new GoToLobbyButtonListener;
    m_pGoToLobbyButtonListener->SetUIButton(*goToLobby);
    m_pGoToLobbyButtonListener->SetHandle(*this);

    UIText* goToLobbyText = new UIText;
    goToLobbyText->SetFont(g_pFontManager->GetFont(Font::kGameOverGoToLobby));
    goToLobbyText->SetSize(D3DXVECTOR2(200.0f, 60.0f));
    goToLobbyText->SetPosition(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
    goToLobbyText->SetText(TEXT("·Îºñ·Î ³ª°¡±â"));
    goToLobbyText->SetColor(D3DCOLOR_XRGB(93, 93, 93));
    goToLobby->AddChild(*goToLobbyText);
}

void GoToLobbyButtonListener::OnMouseEnter()
{
}

void GoToLobbyButtonListener::OnMouseExit()
{
}

void GoToLobbyButtonListener::OnMouseDown(const int key)
{
    g_pUIManager->Destroy(*m_pHandle);
}

void GoToLobbyButtonListener::OnMouseUp(const int key)
{
}

void GoToLobbyButtonListener::OnMouseDrag(const int key)
{
}

void GoToLobbyButtonListener::SetHandle(UIObject& val)
{
    m_pHandle = &val;
}

