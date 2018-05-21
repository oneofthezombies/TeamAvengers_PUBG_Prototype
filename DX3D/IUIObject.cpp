#include "stdafx.h"
#include "IUIObject.h"
#include "UIManager.h"

IUIObject::IUIObject(IUIObjectDelegate* pIUIObjectDelegate, int uiTag)
    : IDisplayObject()
    , m_pIUIObjectDelegate(pIUIObjectDelegate)
    , m_uiTag(uiTag)
    , m_bDrawBorder(true)
    , m_color(D3DCOLOR_XRGB(255, 255, 255))
    , m_bPrevIsMouseOn(false)
    , m_bCurrIsMouseOn(false)
    , m_combinedPos(0.0f, 0.0f, 0.0f)
    , m_pivot(0.0f, 0.0f, 0.0f)
{
    if (pIUIObjectDelegate)
        pIUIObjectDelegate->m_pIUIObject = this;

    ZeroMemory(&m_pivot, sizeof m_pivot);
    ZeroMemory(&m_rect, sizeof m_rect);

    g_pUIManager->AddIUIObject(*this);
}

IUIObject::~IUIObject()
{
    g_pUIManager->RemoveIUIObject(*this);
}

void IUIObject::Init()
{
    // do nothing
}

void IUIObject::Update()
{
	UpdateCombinedPosition();
    GetFinalRect(&m_rect);
    UpdateOnMouseEnterExit();

    UpdateChildren();
}

void IUIObject::Render()
{
	DrawBorder();

    RenderChildren();
}

void IUIObject::DrawBorder()
{
    if (!m_bDrawBorder) return;

    D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);
    vector<VERTEX_RHWC> vertices = 
    {
        VERTEX_RHWC(m_rect.left, m_rect.top, 0, 1, c),
        VERTEX_RHWC(m_rect.right, m_rect.top, 0, 1, c),
        VERTEX_RHWC(m_rect.right, m_rect.bottom, 0, 1, c),
        VERTEX_RHWC(m_rect.left, m_rect.bottom, 0, 1, c),
        VERTEX_RHWC(m_rect.left, m_rect.top, 0, 1, c),
    };

    const auto dv = g_pDevice;
    dv->SetFVF(VERTEX_RHWC::FVF);
    dv->DrawPrimitiveUP(D3DPT_LINESTRIP, vertices.size() - 1, vertices.data(), sizeof VERTEX_RHWC);
}

void IUIObject::UpdateCombinedPosition()
{
	m_combinedPos = m_pos;

	if (m_pParent)
		m_combinedPos += static_cast<IUIObject*>(m_pParent)->GetCombinedPosition();
}

IUIObject* IUIObject::FindChildByUITag(int uiTag)
{
	if (m_uiTag == uiTag)
		return this;

	for (auto p : m_vecPChild)
	{
        IUIObject* pChild = static_cast<IUIObject*>(p)->FindChildByUITag(uiTag);

		if (pChild)
			return pChild;
	}

	return nullptr;
}

void IUIObject::GetFinalRect(RECT* OutRect)
{
	D3DXMATRIXA16 mat;
    g_pSprite->GetTransform(&mat);

    const float left = m_combinedPos.x * mat._11 + mat._41;
    const float top = m_combinedPos.y * mat._22 + mat._42;
    const float right = left + m_size.x * mat._11;
    const float bottom = top + m_size.y * mat._22;

	SetRect(OutRect, 
            static_cast<int>(left), 
            static_cast<int>(top), 
            static_cast<int>(right), 
            static_cast<int>(bottom));
}

void IUIObject::UpdateOnMouseEnterExit()
{
    m_bPrevIsMouseOn = m_bCurrIsMouseOn;
    m_bCurrIsMouseOn = PtInRect(&m_rect, g_pUIManager->GetCurrentMousePos());

    if (!m_bPrevIsMouseOn && m_bCurrIsMouseOn)
    {
        if (m_pIUIObjectDelegate)
            m_pIUIObjectDelegate->OnMouseEnter();
    }

    if (m_bPrevIsMouseOn && !m_bCurrIsMouseOn)
    {
        if (m_pIUIObjectDelegate)
            m_pIUIObjectDelegate->OnMouseExit();
    }
}

const D3DXVECTOR3& IUIObject::GetCombinedPosition()
{
    return m_combinedPos;
}
