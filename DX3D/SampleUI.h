#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
class IUIObject;

class SampleUI :public IDisplayObject, public IUIButtonDelegate
{
private:
	LPD3DXSPRITE m_pSprite;
	IUIObject*   m_pRootUI;
	//LPDIRECT3DTEXTURE9 m_pTex;
	//D3DXIMAGE_INFO m_imageInfo;

public:
	SampleUI();
	~SampleUI();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// Inherited via IUIButtonDelegate
	virtual void OnClick(UIButton * pSender) override;
};

