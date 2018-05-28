#pragma once

#include "UIObject.h"
#include "UIText.h"

class Gun;

class UIInGame : public UIObject
{
private:
    Gun**  m_ppGun;
    string m_numBulletText;

    FIRE_MODE* m_pFireMode;
    string m_fireModeText;

public:
    UIInGame();
    virtual ~UIInGame();

    void Init(Gun** ppGun, FIRE_MODE* pFireMode);
    void Update();

    void UpdateTextNumBullet();
    void UpdateTextFireMode();

    static UIInGame* Create(Gun** ppGun, FIRE_MODE* pFireMode);
};