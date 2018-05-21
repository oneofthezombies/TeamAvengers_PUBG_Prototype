#pragma once

#include "UIImage.h"
#include "UIButton.h"

class IUIButtonListner;

class GameOverUI 
    : public UIImage
{
private:
    IUIButtonListner* m_listner;

public:
    GameOverUI();
    virtual ~GameOverUI();

    virtual void Init() override;
};

class IUIButtonListner
    : public IUIObjectDelegate
    , public IUIButtonDelegate
{
public:
    IUIObject* m_pAttached;

    // Inherited via IUIObjectDelegate
    virtual void OnMouseEnter() override;
    virtual void OnMouseExit() override;

    // Inherited via IUIButtonDelegate
    virtual void OnMouseDown(const MouseButton::Type button) override;
    virtual void OnMouseUp(const MouseButton::Type button) override;
    virtual void OnMouseDrag(const MouseButton::Type button) override;
};