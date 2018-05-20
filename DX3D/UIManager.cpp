#include "stdafx.h"
#include "UIManager.h"
#include "IUIObject.h"
#include "UIText.h"
#include "UIButton.h"

UIManager::UIManager()
    : SingletonBase<UIManager>()
    , m_pSprite(nullptr)
    , m_pSampleUIButtonDelegate(nullptr)
{
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
    D3DXCreateSprite(g_pDevice, &m_pSprite);

    UIText* a = new UIText(g_pFontManager->GetFont(FONT::NORMAL));
    a->Init();
    a->m_text = TEXT("¾È³çÇÏ¼¼¿ä.");
    a->m_size = D3DXVECTOR2(200.0f, 200.0f);

    m_pSampleUIButtonDelegate = new SampleUIButtonDelegate;
    UIButton* b = new UIButton(m_pSampleUIButtonDelegate, m_pSampleUIButtonDelegate);
    b->Init();
    b->m_size = D3DXVECTOR2(200.0f, 200.f);
}

void UIManager::Destroy()
{
    deque<IUIObject*> q(m_usetIUIObject.begin(), m_usetIUIObject.end());

    while (!q.empty())
    {
        auto u = q.front();
        q.pop_front();

        SAFE_RELEASE(u);
    }

    SAFE_RELEASE(m_pSprite);
}

void UIManager::Update()
{
    m_prevMousePos = m_currMousePos;
    GetCursorPos(&m_currMousePos);
    ScreenToClient(g_hWnd, &m_currMousePos);

    m_prevIsPushedMouseButtonLeft = m_currIsPushedMouseButtonLeft;
    m_currIsPushedMouseButtonLeft = GetKeyState(VK_LBUTTON) & 0x8000;
    m_prevIsPushedMouseButtonRight = m_currIsPushedMouseButtonRight;
    m_currIsPushedMouseButtonRight = GetKeyState(VK_RBUTTON) & 0x8000;

    RECT rect;
    GetClientRect(g_hWnd, &rect);
    const int width = rect.right - rect.left;
    const int height = rect.bottom - rect.top;

    D3DXMATRIXA16 mat;
    //D3DXMatrixScaling(&mat, static_cast<float>(width) / 1920.0f, static_cast<float>(height) / 1080.0f, 0.0f);
    D3DXMatrixIdentity(&mat);

    m_pSprite->SetTransform(&mat);

    for (auto u : m_usetIUIObject)
        SAFE_UPDATE(u);
}

void UIManager::Render()
{
    if (!m_pSprite) return;

    const auto dv = g_pDevice;
    dv->SetTexture(0, nullptr);
    m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

    for (auto u : m_usetIUIObject)
        SAFE_RENDER(u);

    m_pSprite->End();
}

void UIManager::AddIUIObject(IUIObject& val)
{
    m_usetIUIObject.emplace(&val);
}

void UIManager::RemoveIUIObject(IUIObject& val)
{
    m_usetIUIObject.erase(&val);
}

const LPD3DXSPRITE UIManager::GetSprite() const
{
    return m_pSprite;
}

const POINT& UIManager::GetCurrentMousePos() const
{
    return m_currMousePos;
}

const POINT& UIManager::GetPreviousMousePos() const
{
    return m_prevMousePos;
}

bool UIManager::IsPushedMouseButtonLeft() const
{
    return m_currIsPushedMouseButtonLeft;
}

bool UIManager::GetPreviousIsPushedMouseButtonLeft() const
{
    return m_prevIsPushedMouseButtonLeft;
}

bool UIManager::IsPushedMouseButtonRight() const
{
    return m_currIsPushedMouseButtonRight;
}

bool UIManager::GetPreviousIsPushedMouseButtonRight() const
{
    return m_prevIsPushedMouseButtonRight;
}


