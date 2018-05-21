#pragma once

#include "SingletonBase.h"

#define g_pUIManager UIManager::GetInstance()
#define g_pSprite    UIManager::GetInstance()->GetSprite()

class IUIObject;
class SampleUIButtonDelegate;

class UIManager
    : public SingletonBase<UIManager>
{
private:
    LPD3DXSPRITE              m_pSprite;

    unordered_set<IUIObject*> m_usetIUIObject;
    deque<IUIObject*>         m_toDeletes;
    int                       m_instanceID;
    
    POINT m_prevMousePos;
    POINT m_currMousePos;
    bool m_prevIsPushedMouseButtonLeft;
    bool m_currIsPushedMouseButtonLeft;
    bool m_prevIsPushedMouseButtonRight;
    bool m_currIsPushedMouseButtonRight;

    SampleUIButtonDelegate* m_pSampleUIButtonDelegate;

    UIManager();
    virtual ~UIManager();

public:
    void Init();
    void Destroy();
    void Destroy(IUIObject& val);
    void Destroy(const int instanceID);

    void Update();
    void Render();

    void AddIUIObject(IUIObject& val);
    void RemoveIUIObject(IUIObject& val);

    void UpdateToDeletes();


    const LPD3DXSPRITE GetSprite() const;
    const POINT& GetCurrentMousePos() const;
    const POINT& GetPreviousMousePos() const;
    bool IsPushedMouseButtonLeft() const;
    bool GetPreviousIsPushedMouseButtonLeft() const;
    bool IsPushedMouseButtonRight() const;
    bool GetPreviousIsPushedMouseButtonRight() const;

    friend SingletonBase<UIManager>;
};
