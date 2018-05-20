#include "stdafx.h"
#include "UIText.h"
#include "UIManager.h"

UIText::UIText(LPD3DXFONT pFont, IUIObjectDelegate* pIUIObjectDelegate, int uiTag)
	: IUIObject(pIUIObjectDelegate, uiTag)
	, m_pFont(pFont)
	, m_drawTextFormat(DT_CENTER | DT_VCENTER) //텍스트 정렬방식
{
}

UIText::~UIText()
{
}

void UIText::Render()
{
	//RECT rect;
	//SetRect(&rect, m_combinedPos.x, m_combinedPos.y, m_combinedPos.x + m_size.x, m_combinedPos.y + m_size.y);

	m_pFont->DrawText(g_pSprite, m_text, lstrlen(m_text), &m_rect, m_drawTextFormat, m_color);

	IUIObject::Render();
}
