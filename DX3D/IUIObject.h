#pragma once
#include "IDisplayObject.h"

class IUIObject;

class IUIObjectDelegate
{
public:
    IUIObject* m_pIUIObject;

    IUIObjectDelegate()
        : m_pIUIObject(nullptr)
    {
    }

    ~IUIObjectDelegate() = default;

    virtual void OnMouseEnter() = 0;
    virtual void OnMouseExit() = 0;
};

class IUIObject 
    : public IDisplayObject
{
private:
    IUIObjectDelegate* m_pIUIObjectDelegate;

    const D3DXVECTOR3& GetCombinedPosition();
    void DrawBorder();

protected:
    RECT m_rect;
    bool m_bPrevIsMouseOn;
    bool m_bCurrIsMouseOn;

public:
	int				m_uiTag;
    D3DXVECTOR3		m_combinedPos;
    D3DXVECTOR3		m_pivot;
	D3DXVECTOR2		m_size;
	D3DCOLOR		m_color;
	bool			m_bDrawBorder;

	IUIObject(IUIObjectDelegate* pIUIObjectDelegate = nullptr, int uiTag = -1);
	virtual ~IUIObject();

	// Inherited via IDisplayObject
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

    void UpdateCombinedPosition();
    void GetFinalRect(RECT* OutRect);
    void UpdateOnMouseEnterExit();

    IUIObject* FindChildByUITag(int uiTag);
};

