#pragma once

#include "UIButton.h"

class SampleUIButtonListner : public IUIButtonOnMouseListner
{
public:
    virtual void OnMouseEnter() override;
    virtual void OnMouseExit() override;
    virtual void OnMouseDown(const int key) override;
    virtual void OnMouseUp(const int key) override;
    virtual void OnMouseDrag(const int key) override;
};