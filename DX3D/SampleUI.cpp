#include "stdafx.h"
#include "SampleUI.h"
#include "IUIObject.h"
#include "UIImage.h"
#include "UIText.h"


enum
{
	UITAG_TEXTVIEW,
	UITAG_BUTTON1,
	UITAG_BUTTON2
};

SampleUI::SampleUI()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
}


SampleUI::~SampleUI()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pRootUI);
	m_pRootUI->ReleaseAll();
}

void SampleUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	{
		UIImage* pImage = new UIImage(m_pSprite);
		pImage->SetTexture("resources/ui/panel-info.png.png");
		//pImage->SetPosition(&D3DXVECTOR3(200, 0, 0));
		m_pRootUI = pImage;
	}
	{
		UIText* pText = new UIText(g_pFontMgr->GetFont(FONT::NORMAL), m_pSprite, UITAG_TEXTVIEW);
		m_pRootUI->AddChild(pText);
		pText->m_text = _T("Push the button");
		pText->m_size = D3DXVECTOR2(312, 200);
		pText->SetPosition(&D3DXVECTOR3(100, 100, 0));
	}

	{
		UIButton* pButton = new UIButton(this, m_pSprite, UITAG_BUTTON1);
		m_pRootUI->AddChild(pButton);
		pButton->SetPosition(&D3DXVECTOR3(135, 330, 0));
		pButton->SetTexture(
			"resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png" );
		pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button1"));
	}

	{
		UIButton* pButton = new UIButton(this, m_pSprite, UITAG_BUTTON2);
		m_pRootUI->AddChild(pButton);
		pButton->SetPosition(&D3DXVECTOR3(135, 400, 0));
		pButton->SetTexture(
			"resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");
		pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button2"));
	}
	D3DXMATRIXA16 matT,matS;
	D3DXMatrixScaling(&matS, 1.5f, 1.5f, 1);
	D3DXMatrixTranslation(&matT, 150, 150, 0);
	m_matWorld = matS*matT;
	////D3DXCreateTextureFromFile(g_pDevice, _T("resources/images/ham1.png"), &m_pTex);
	//D3DXCreateTextureFromFileEx(
	//	g_pDevice,				//LPDIRECT3DDEVICE9 pDevice,
	//	_T("resources/images/ham1.png"),	//LPCTSTR pSrcFile,
	//	D3DX_DEFAULT_NONPOW2,	//UINT Width,
	//	D3DX_DEFAULT_NONPOW2,	//UINT Height,
	//	D3DX_DEFAULT,		//UINT MipLevels,
	//	0,					//DWORD Usage,
	//	D3DFMT_UNKNOWN,		//D3DFORMAT Format,
	//	D3DPOOL_MANAGED,	//D3DPOOL Pool
	//	D3DX_FILTER_NONE,	//DWORD Filter
	//	D3DX_DEFAULT,		//DWORD MipFilter
	//	D3DCOLOR_XRGB(255, 255, 255),	//D3DCOLOR ColorKey
	//	&m_imageInfo,	//D3DXIMAGE_INFO *pSrcInfo
	//	NULL,			//PALETTEENTRY *pPalette
	//	&m_pTex);	//LPDIRECT3DTEXTURE9 *ppTexture
}

void SampleUI::Update()
{
	SAFE_UPDATE(m_pRootUI);
}

void SampleUI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND/*|D3DXSPRITE_SORT_TEXTURE*/);
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
	m_pSprite->End();
	//RECT clientRect;
	//GetClientRect(g_hWnd, &clientRect);
	//D3DXMATRIXA16 matR, matT, matWorld;
	//static float fAngle = 0.0f;
	//fAngle += 0.1f;
	//D3DXMatrixRotationZ(&matR, fAngle);
	//D3DXMatrixIdentity(&matT);
	//D3DXMatrixTranslation(&matT, clientRect.right - m_imageInfo.Width, 0, 0);
	//matWorld = matR * matT;
	//
	//RECT rc;
	//SetRect(&rc, 0, 0, m_imageInfo.Width, m_imageInfo.Height);
	////D3DXSPRITE_ALPHABLEND
	//m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//m_pSprite->SetTransform(&matWorld);
	//m_pSprite->Draw(
	//	m_pTex,
	//	&rc,
	//	&D3DXVECTOR3(m_imageInfo.Width / 2, m_imageInfo.Height / 2, 0),
	//	//&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	WHITE);
	//m_pSprite->End();
}

void SampleUI::OnClick(UIButton * pSender)
{
	if (pSender->m_uiTag == UITAG_BUTTON1)
	{
		UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
		pText->m_text = _T("Button1 pushed");
	}
	else if (pSender->m_uiTag == UITAG_BUTTON2)
	{
		UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
		pText->m_text = _T("Button2 pushed");
	}
}
