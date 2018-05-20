#include "stdafx.h"
#include "UIButton.h"
#include "UIManager.h"
#include "UIText.h"

UIButton::UIButton(IUIButtonDelegate* pIUIButtonDelegate, IUIObjectDelegate* pIUIObjectDelegate, int uiTag)
	: IUIObject(pIUIObjectDelegate, uiTag)
	, m_pIUIButtonDelegate(pIUIButtonDelegate)
	, m_state(State::kIdle)
    , m_mouseButtonToRespond(MouseButton::Type::kLeft)
{
    if (pIUIButtonDelegate)
        pIUIButtonDelegate->m_pUIButton = this;

    m_vecTexture.resize(m_kNumState, nullptr);
}

UIButton::~UIButton()
{
}

void UIButton::Update()
{
    UpdateCombinedPosition();
    GetFinalRect(&m_rect);
    UpdateOnMouseEnterExit();
    UpdateOnMouseDownUpDrag();

    UpdateChildren();
}

void UIButton::Render()
{
	if (m_vecTexture[m_state])
	{
		RECT size;
		SetRect(&size, 0, 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y));

        g_pSprite->Draw(m_vecTexture[m_state], &size, &m_pivot, &m_combinedPos, m_color);
	}

	IUIObject::Render();
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
	m_size.x = info.Width;
	m_size.y = info.Height;
}

void UIButton::SetText(LPD3DXFONT font, LPCTSTR text)
{
	UIText* pText = new UIText(font);
	AddChild(pText);
	pText->m_text = text;
	pText->m_size = m_size;
}

void UIButton::SetMouseButtonToRespond(const MouseButton::Type flag)
{
    m_mouseButtonToRespond = flag;
}

void UIButton::UpdateOnMouseDownUpDrag()
{
    const auto uiMgr = g_pUIManager;

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
            if (m_mouseButtonToRespond == MouseButton::kLeft)
            {
                if (uiMgr->IsPushedMouseButtonLeft())
                {
                    m_state = State::kSelect;

                    if (m_pIUIButtonDelegate)
                        m_pIUIButtonDelegate->OnMouseDown(m_mouseButtonToRespond);
                }
            }
            else if (m_mouseButtonToRespond == MouseButton::kRight)
            {
                if (uiMgr->IsPushedMouseButtonRight())
                {
                    m_state = State::kSelect;

                    if (m_pIUIButtonDelegate)
                        m_pIUIButtonDelegate->OnMouseDown(m_mouseButtonToRespond);
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
            if (m_mouseButtonToRespond == MouseButton::kLeft)
            {
                if (uiMgr->IsPushedMouseButtonLeft())
                {
                    if (m_bCurrIsMouseOn)
                        if (m_pIUIButtonDelegate)
                            m_pIUIButtonDelegate->OnMouseDrag(m_mouseButtonToRespond);
                }
                else
                {
                    if (m_bCurrIsMouseOn)
                    {
                        m_state = State::kMouseOver;

                        if (uiMgr->GetPreviousIsPushedMouseButtonLeft())
                            if (m_pIUIButtonDelegate)
                                m_pIUIButtonDelegate->OnMouseUp(m_mouseButtonToRespond);
                    }
                    else
                    {
                        m_state = State::kIdle;
                    }
                }
            }
            else if (m_mouseButtonToRespond == MouseButton::kRight)
            {
                if (uiMgr->IsPushedMouseButtonRight())
                {
                    if (m_bCurrIsMouseOn)
                        if (m_pIUIButtonDelegate)
                            m_pIUIButtonDelegate->OnMouseDrag(m_mouseButtonToRespond);
                }
                else
                {
                    if (m_bCurrIsMouseOn)
                    {
                        m_state = State::kMouseOver;

                        if (uiMgr->GetPreviousIsPushedMouseButtonRight())
                            if (m_pIUIButtonDelegate)
                                m_pIUIButtonDelegate->OnMouseUp(m_mouseButtonToRespond);
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

void SampleUIButtonDelegate::OnMouseDown(const MouseButton::Type button)
{
    cout << "OnMouseDown()\n";
}

void SampleUIButtonDelegate::OnMouseUp(const MouseButton::Type button)
{
    cout << "OnMouseUp()\n";
}

void SampleUIButtonDelegate::OnMouseDrag(const MouseButton::Type button)
{
    cout << "OnMouseDrag()\n";
}

void SampleUIButtonDelegate::OnMouseEnter()
{
    cout << "OnMouseEnter()\n";
}

void SampleUIButtonDelegate::OnMouseExit()
{
    cout << "OnMouseExit()\n";
}
