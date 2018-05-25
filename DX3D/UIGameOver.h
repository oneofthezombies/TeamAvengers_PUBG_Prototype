#pragma once

#include "UIImage.h"
#include "UIButton.h"

class GoToLobbyButtonListener;

class UIGameOver 
    : public UIImage
{
private:
    std::wstring temp;
    GoToLobbyButtonListener* m_pGoToLobbyButtonListener;

public:
    UIGameOver();
    virtual ~UIGameOver();

    virtual void Init() override;
};

class GoToLobbyButtonListener : public IUIButtonOnMouseListener
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