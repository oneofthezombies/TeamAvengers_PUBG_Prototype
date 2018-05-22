#include "stdafx.h"
#include "UIButton.h"
#include "UIManager.h"
#include "UIText.h"

UIButton::UIButton()
    : UIObject()
    , m_state(State::kIdle)
    , m_KeyToRespond(VK_LBUTTON)
    , m_pIUIButtonOnMouseListner(nullptr)
{
    m_vecTexture.resize(m_kNumState, nullptr);
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
    UpdateViewportPosRect();
    UpdateOnMouse();
    UpdateChildren();
}

void UIButton::Render()
{
	if (m_vecTexture[m_state])
	{
		RECT rect;
		SetRect(&rect, 0, 0, static_cast<int>(m_vSize.x), static_cast<int>(m_vSize.y));

        g_pSprite->Draw(m_vecTexture[m_state], &rect, &m_vCenter, &m_vViewportPosition, m_color);
	}

	UIObject::Render();
}

void UIButton::UpdateOnMouse()
{
    UpdateOnMouseEnterExit();
    UpdateOnMouseDownUpDrag();
}

void UIButton::SetTexture(const string& idle, const string& mouseOver, const string& select)
{
    const auto texMgr = g_pTextureManager;
    if (!texMgr) return;

	D3DXIMAGE_INFO info;
	m_vecTexture[State::kIdle]= texMgr->GetTexture(idle);
	m_vecTexture[State::kMouseOver] = texMgr->GetTexture(mouseOver);
	m_vecTexture[State::kSelect] = texMgr->GetTexture(select);

	D3DXGetImageInfoFromFileA(idle.c_str(), &info);
	m_vSize.x = info.Width;
	m_vSize.y = info.Height;
}

void UIButton::SetText(const LPD3DXFONT font, const LPCTSTR text)
{
	UIText* pText = new UIText;
	AddChild(*pText);
    pText->SetFont(font);
    pText->SetText(text);
    pText->SetSize(m_vSize);
}

void UIButton::SetKeyToRespond(const int key)
{
    m_KeyToRespond = key;
}

void UIButton::SetIUIButtonOnMouseListner(IUIButtonOnMouseListner& val)
{
    m_pIUIButtonOnMouseListner = &val;
}

void UIButton::UpdateOnMouseEnterExit()
{
    if (!m_pIUIButtonOnMouseListner) return;

    m_bPrevIsMouseOn = m_bCurrIsMouseOn;
    m_bCurrIsMouseOn = PtInRect(&m_rect, g_pUIManager->GetCurrentMousePos());

    if (!m_bPrevIsMouseOn && m_bCurrIsMouseOn)
        m_pIUIButtonOnMouseListner->OnMouseEnter();

    if (m_bPrevIsMouseOn && !m_bCurrIsMouseOn)
        m_pIUIButtonOnMouseListner->OnMouseExit();
}

void UIButton::UpdateOnMouseDownUpDrag()
{
    const auto uiMgr = g_pUIManager;
    if (!uiMgr) return;

    switch (m_state)
    {
    case State::kIdle:
        {
            if (m_bCurrIsMouseOn)
            {
                m_state = State::kMouseOver;
            }
        }
        break;
    case State::kMouseOver:
        {
            if (m_KeyToRespond == VK_LBUTTON)
            {
                if (uiMgr->IsPushedMouseButtonLeft())
                {
                    m_state = State::kSelect;

                    if (m_pIUIButtonOnMouseListner)
                        m_pIUIButtonOnMouseListner->OnMouseDown(m_KeyToRespond);
                }
            }
            else if (m_KeyToRespond == VK_RBUTTON)
            {
                if (uiMgr->IsPushedMouseButtonRight())
                {
                    m_state = State::kSelect;

                    if (m_pIUIButtonOnMouseListner)
                        m_pIUIButtonOnMouseListner->OnMouseDown(m_KeyToRespond);
                }
            }
            else
            {
                // something error
            }
        }
        break;
    case State::kSelect:
        {
            if (m_KeyToRespond == VK_LBUTTON)
            {
                if (uiMgr->IsPushedMouseButtonLeft())
                {
                    if (m_bCurrIsMouseOn)
                        if (m_pIUIButtonOnMouseListner)
                            m_pIUIButtonOnMouseListner->OnMouseDrag(m_KeyToRespond);
                }
                else
                {
                    if (m_bCurrIsMouseOn)
                    {
                        m_state = State::kMouseOver;

                        if (uiMgr->GetPreviousIsPushedMouseButtonLeft())
                            if (m_pIUIButtonOnMouseListner)
                                m_pIUIButtonOnMouseListner->OnMouseUp(m_KeyToRespond);
                    }
                    else
                    {
                        m_state = State::kIdle;
                    }
                }
            }
            else if (m_KeyToRespond == VK_RBUTTON)
            {
                if (uiMgr->IsPushedMouseButtonRight())
                {
                    if (m_bCurrIsMouseOn)
                        if (m_pIUIButtonOnMouseListner)
                            m_pIUIButtonOnMouseListner->OnMouseDrag(m_KeyToRespond);
                }
                else
                {
                    if (m_bCurrIsMouseOn)
                    {
                        m_state = State::kMouseOver;

                        if (uiMgr->GetPreviousIsPushedMouseButtonRight())
                            if (m_pIUIButtonOnMouseListner)
                                m_pIUIButtonOnMouseListner->OnMouseUp(m_KeyToRespond);
                    }
                    else
                    {
                        m_state = State::kIdle;
                    }
                }
            }
            else
            {
                // something error
            }
        }
        break;
    default:
        {
            // something error
        }
        break;
    }
}

IUIButtonOnMouseListner::IUIButtonOnMouseListner()
    : m_pUIButton(nullptr)
{
}

void IUIButtonOnMouseListner::SetUIButton(UIButton& val)
{
    m_pUIButton = &val;
    m_pUIButton->SetIUIButtonOnMouseListner(*this);
}

UIButton* IUIButtonOnMouseListner::GetUIButton() const
{
    return m_pUIButton;
}
