#pragma once

#include "UIObject.h"
#include "UIText.h"

class Gun;

class UIInGame : public UIObject
{
private:
    Gun**  m_ppGun;
    string m_numBulletText;

public:
    UIInGame();
    virtual ~UIInGame();

    void Init(Gun** ppGun);
    void Update();

    void UpdateTextNumBullet();

    static UIInGame* Create(Gun** ppGun);
};