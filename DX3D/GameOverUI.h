#pragma once

#include "UIImage.h"
#include "UIButton.h"

class GoToLobbyButtonListner;

class GameOverUI 
    : public UIImage
{
private:
    GoToLobbyButtonListner* m_pGoToLobbyButtonListner;

public:
    GameOverUI();
    virtual ~GameOverUI();

    virtual void Init() override;
};

class GoToLobbyButtonListner : public IUIButtonOnMouseListner
{
    UIObject* m_pHandle;

public:
    virtual void OnMouseEnter() override;
    virtual void OnMouseExit() override;
    virtual void OnMouseDown(const int key) override;
    virtual void OnMouseUp(const int key) override;
    virtual void OnMouseDrag(const int key) override;

    void SetHandle(UIObject& val);
};