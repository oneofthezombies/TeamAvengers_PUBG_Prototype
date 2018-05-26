#pragma once

#include "UIImage.h"
#include "UIButton.h"

class UILobbyButtonOnMouseListener : public IUIButtonOnMouseListener
{
public:
    UILobbyButtonOnMouseListener();
    virtual ~UILobbyButtonOnMouseListener() = default;

    virtual void OnMouseEnter() override;
    virtual void OnMouseExit() override;
    virtual void OnMouseDown(const int key) override;
    virtual void OnMouseUp(const int key) override;
    virtual void OnMouseDrag(const int key) override;
};

class UILobby : public UIImage
{
private:
    UILobbyButtonOnMouseListener* m_UILobbyButtonOnMouseListener;

public:
    UILobby();
    virtual ~UILobby();

    void Init();
};