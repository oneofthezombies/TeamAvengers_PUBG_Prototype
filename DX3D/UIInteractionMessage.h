#pragma once
#include "UIObject.h"

class UIInteractionMessage : public UIObject
{
private:

public:
    UIInteractionMessage();
    virtual ~UIInteractionMessage();

    virtual void Init() override;
};