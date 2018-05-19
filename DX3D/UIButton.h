#pragma once
#include "IUIObject.h"

class UIButton;

class IUIButtonDelegate
{
public:
	virtual void OnClick(UIButton* pSender) = 0;
};

class UIButton : public IUIObject
{
private:
	enum ButtonState
	{
		NORMAL,
		MOUSEOVER,
		SELECTED,
		COUNT
	};
	ButtonState m_buttonState;
public:
	IUIButtonDelegate * m_pDelegate;
	LPDIRECT3DTEXTURE9 m_aTexture[COUNT];

	UIButton(IUIButtonDelegate* pDelegate, LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~UIButton();

	virtual void Update() override;
	virtual void Render() override;

	void SetTexture(string normal, string mouseOver, string selected);
	void SetText(LPD3DXFONT font, LPCTSTR text);

};

