#include "stdafx.h"
#include "UIImage.h"
#include "UIManager.h"

UIImage::UIImage()
    : UIObject()
    , m_pTex(nullptr)
{
}

UIImage::~UIImage()
{
}

void UIImage::Render()
{
	if (m_pTex)
	{
		RECT rect;
		SetRect(&rect, 0, 0, static_cast<int>(m_vSize.x), static_cast<int>(m_vSize.y));
		g_pSprite->Draw(m_pTex, &rect, &m_vCenter, &m_vViewportPosition, m_color);
	}

	UIObject::Render();
}

void UIImage::SetTexture(const string fullPath)
{
	D3DXIMAGE_INFO info;
	m_pTex = g_pTextureManager->GetTexture(fullPath);
	D3DXGetImageInfoFromFileA(fullPath.c_str(), &info);
	m_vSize.x = info.Width;
	m_vSize.y = info.Height;
}
