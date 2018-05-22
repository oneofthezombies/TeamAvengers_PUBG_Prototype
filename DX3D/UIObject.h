#pragma once
#include "IDisplayObject.h"

class UIObject
{
private:
    D3DXVECTOR3 m_vPosition;
    int         m_instanceID;

    void DrawBorder();
    void UpdateRect();

    void UpdateViewportPosition();
    void SetParent(UIObject& parent);
    const D3DXVECTOR3& GetViewportPosition() const;

protected:
    D3DXVECTOR3 m_vViewportPosition;
    D3DXVECTOR3	m_vCenter;
    D3DXVECTOR2 m_vSize;
    RECT        m_rect;
    D3DCOLOR    m_color;

    deque<UIObject*> m_deqPChildren;
    UIObject*        m_pParent;

    void UpdateViewportPosRect();

public:
	UIObject();
	virtual ~UIObject();

    virtual void Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void ReleaseChildren();
    void UpdateChildren();
    void RenderChildren();

    void SetInstanceID(const int val);
    int GetInstanceID() const;
    void AddChild(UIObject& child);
    void SetPosition(const D3DXVECTOR3& val);
    void SetCenter(const D3DXVECTOR3& val);
    void SetSize(const D3DXVECTOR2& val);
    void SetColor(const D3DCOLOR& val);
};
