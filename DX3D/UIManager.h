#pragma once

#include "SingletonBase.h"
#include "UIObject.h"
#include "UIButton.h"

#define g_pUIManager UIManager::GetInstance()
#define g_pSprite    UIManager::GetInstance()->GetSprite()

class UIText;
class UIImage;
class SampleUIListner;

class UIManager : public SingletonBase<UIManager>
{
private:
    LPD3DXSPRITE m_pSprite;

    unordered_set<UIObject*>        m_usetUIObjects;
    unordered_map<UIObject*, float> m_umapToDeleteUIObjects;
    int                             m_UIObjectInstanceID;
    bool                            m_bIsDrawBorder;

    POINT m_prevMousePos;
    POINT m_currMousePos;
    bool  m_prevIsPushedMouseButtonLeft;
    bool  m_currIsPushedMouseButtonLeft;
    bool  m_prevIsPushedMouseButtonRight;
    bool  m_currIsPushedMouseButtonRight;

    UIManager();
    virtual ~UIManager();

    void InitSprite();
    void UpdateToDeleteUIObjects();

public:
    void Init();
    void Destroy();
    void Update();
    void Render();

    void RegisterUIObject(UIObject& val);
    void Destroy(UIObject& val, const float t = 0.0f);
    void Destroy(const int instanceID, const float t = 0.0f);

    const LPD3DXSPRITE GetSprite() const;
    void SetIsDrawBorder(const bool val);
    bool IsDrawBorder() const;

    const POINT& GetCurrentMousePos() const;
    const POINT& GetPreviousMousePos() const;
    bool IsPushedMouseButtonLeft() const;
    bool GetPreviousIsPushedMouseButtonLeft() const;
    bool IsPushedMouseButtonRight() const;
    bool GetPreviousIsPushedMouseButtonRight() const;

    friend SingletonBase<UIManager>;
};
