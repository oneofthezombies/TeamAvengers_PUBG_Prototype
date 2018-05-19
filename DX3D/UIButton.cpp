#include "stdafx.h"
#include "UIButton.h"
#include "UIText.h"

UIButton::UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite, int uiTag)
	:IUIObject(pSprite,uiTag)
	,m_pDelegate(pDelegate)
	,m_buttonState(NORMAL)
{
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
	IUIObject::Update();

	RECT rect;
	GetFinalRect(&rect);

	POINT mousePoint;
	GetCursorPos(&mousePoint);//여기까지는 screen기준.
	ScreenToClient(g_hWnd,&mousePoint);//window기준

	//마우스 포인터가 버튼 영역 안에 있을때
	if (PtInRect(&rect, mousePoint))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_buttonState == MOUSEOVER)
			{
				m_buttonState = SELECTED;
			}
		}
		else
		{
			if (m_buttonState == SELECTED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSEOVER;
		}
	}
	else//마우스 포인터가 버튼 영역 밖에 있을때
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{

		}
		else
		{
			m_buttonState = NORMAL;
		}
	}
}

void UIButton::Render()
{
	if (m_aTexture[m_buttonState])
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);

		m_pSprite->Draw(m_aTexture[m_buttonState], &rect, &m_pivot, &m_combinedPos, m_color);
	}
	IUIObject::Render();
}

void UIButton::SetTexture(string normal, string mouseOver, string selected)
{
	D3DXIMAGE_INFO info;
	m_aTexture[NORMAL]= g_pTextureManager->GetTexture(normal);
	m_aTexture[MOUSEOVER] = g_pTextureManager->GetTexture(mouseOver);
	m_aTexture[SELECTED] = g_pTextureManager->GetTexture(selected);

	D3DXGetImageInfoFromFileA(normal.c_str(), &info);
	m_size.x = info.Width;
	m_size.y = info.Height;
}

void UIButton::SetText(LPD3DXFONT font, LPCTSTR text)
{
	UIText* pText = new UIText(font, m_pSprite);
	this->AddChild(pText);
	pText->m_text = text;
	pText->m_size = m_size;
}
