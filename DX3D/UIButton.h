#pragma once
#include "IUIObject.h"

struct MouseButton
{
    enum Type : int
    {
        kLeft = 1,
        kRight
    };
};

class UIButton;

class IUIButtonDelegate
{
public:
    UIButton* m_pUIButton;

    IUIButtonDelegate()
        : m_pUIButton(nullptr)
    {
    }
    ~IUIButtonDelegate() = default;

    virtual void OnMouseDown(const MouseButton::Type button) = 0;
    virtual void OnMouseUp(const MouseButton::Type button) = 0;
    virtual void OnMouseDrag(const MouseButton::Type button) = 0;
};

class UIButton 
    : public IUIObject
{
private:
	enum State
	{
        kIdle,
        kMouseOver,
        kSelect,
	};
    static const int m_kNumState = 3;

	State m_state;
    MouseButton::Type m_mouseButtonToRespond;

public:
	IUIButtonDelegate* m_pIUIButtonDelegate;
	vector<LPDIRECT3DTEXTURE9> m_vecTexture;

	UIButton(IUIButtonDelegate* pIUIButtonDelegate, IUIObjectDelegate* pIUIObjectDelegate = nullptr, int uiTag = -1);
	virtual ~UIButton();

	virtual void Update() override;
	virtual void Render() override;

	void SetTexture(const string& idle, const string& mouseOver, const string& select);
	void SetText(LPD3DXFONT font, LPCTSTR text);
    void SetMouseButtonToRespond(const MouseButton::Type flag);
    void UpdateOnMouseDownUpDrag();
};

class SampleUIButtonDelegate
    : public IUIObjectDelegate 
    , public IUIButtonDelegate
{
public:
    // Inherited via IUIObjectDelegate
    virtual void OnMouseEnter() override;
    virtual void OnMouseExit() override;

    // Inherited via IUIButtonDelegate
    virtual void OnMouseDown(const MouseButton::Type button) override;
    virtual void OnMouseUp(const MouseButton::Type button) override;
    virtual void OnMouseDrag(const MouseButton::Type button) override;
};