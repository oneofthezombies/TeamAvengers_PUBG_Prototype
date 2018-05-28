#pragma once

#include "UIImage.h"
#include "UIButton.h"

class GoToLobbyButtonListener;

class UIGameOver 
    : public UIImage
{
private:
    string m_temp;
    GoToLobbyButtonListener* m_pGoToLobbyButtonListener;

public:
    UIGameOver();
    virtual ~UIGameOver();

    void Init(bool isWon, const int rank, const int total);
};

class GoToLobbyButtonListener : public IUIButtonOnMouseListener
{
public:
    virtual void OnMouseEnter() override;
    virtual void OnMouseExit() override;
    virtual void OnMouseDown(const int key) override;
    virtual void OnMouseUp(const int key) override;
    virtual void OnMouseDrag(const int key) override;
};