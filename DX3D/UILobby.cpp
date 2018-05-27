#include "stdafx.h"
#include "UILobby.h"

UILobby::UILobby()
    : UIImage()
    , m_UILobbyButtonOnMouseListener(nullptr)
{
}

UILobby::~UILobby()
{
    SAFE_DELETE(m_UILobbyButtonOnMouseListener);
}

void UILobby::Init()
{
    g_pUIManager->RegisterUIObject(*this);
    SetTexture("resources/images/background.png");

    UIButton* startButton = UIButton::Create("resources/images/start_btn_default.png", 
                                             "resources/images/start_btn_mouseover.png", 
                                             "resources/images/start_btn_clicked.png", 
                                             D3DXVECTOR3(729.0f, 536.0f, 0.0f), this);

    m_UILobbyButtonOnMouseListener = new UILobbyButtonOnMouseListener;
    m_UILobbyButtonOnMouseListener->SetUIButton(*startButton);
    m_UILobbyButtonOnMouseListener->SetHandle(*this);
}

UILobbyButtonOnMouseListener::UILobbyButtonOnMouseListener()
    : IUIButtonOnMouseListener()
{
}

void UILobbyButtonOnMouseListener::OnMouseEnter()
{
}

void UILobbyButtonOnMouseListener::OnMouseExit()
{
}

void UILobbyButtonOnMouseListener::OnMouseDown(const int key)
{
}

void UILobbyButtonOnMouseListener::OnMouseUp(const int key)
{
    g_pUIManager->Destroy(*GetHandle());
    g_pSceneManager->SetCurrentScene(SCENE_INDEX::SCENE_SHOTTING);
}

void UILobbyButtonOnMouseListener::OnMouseDrag(const int key)
{
}
