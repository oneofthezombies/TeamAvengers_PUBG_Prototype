#pragma once
#include "IUIObject.h"

class UIImage 
    : public IUIObject
{
public:
	LPDIRECT3DTEXTURE9 m_pTex;

	UIImage(IUIObjectDelegate* pIUIObjectDelegate = nullptr, int uiTag = -1);
	virtual ~UIImage();

	virtual void Render() override;

	void SetTexture(string fullPath);
};

