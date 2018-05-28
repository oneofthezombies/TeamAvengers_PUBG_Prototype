#pragma once

#include "IScene.h"

class SceneLobby : public IScene
{
public:
    SceneLobby();
    virtual ~SceneLobby();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};