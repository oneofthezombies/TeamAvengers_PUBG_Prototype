#pragma once
#include "UIObject.h"

class UIText : public UIObject
{
private:
    LPD3DXFONT m_pFont;
    string	   m_textString;
    LPCTSTR    m_text;
    DWORD	   m_drawTextFormat;

public:
	UIText();
	virtual ~UIText();

	virtual void Render() override;

    void SetFont(const LPD3DXFONT val);
    void SetText(const LPCTSTR val);
    void SetText(const string& val);
    void SetDrawTextFormat(const DWORD val);
};

