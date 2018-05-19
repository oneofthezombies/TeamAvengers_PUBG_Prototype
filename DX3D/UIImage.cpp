#include "stdafx.h"
#include "UIImage.h"


UIImage::UIImage(LPD3DXSPRITE pSprite, int uiTag)
	: IUIObject(pSprite,uiTag)
	, m_pTex(NULL)
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
		SetRect(&rect, 0, 0, m_size.x, m_size.y);

		m_pSprite->Draw(m_pTex, &rect, &m_pivot, &m_combinedPos, m_color);
	}
	IUIObject::Render();
}

void UIImage::SetTexture(string fullPath)
{
	D3DXIMAGE_INFO info;
	m_pTex = g_pTextureManager->GetTexture(fullPath);
	D3DXGetImageInfoFromFileA(fullPath.c_str(), &info);
	m_size.x = info.Width;
	m_size.y = info.Height;
}
