#pragma once
#include "BaseObject.h"

class IDisplayObject : public BaseObject
{
protected:
	D3DXVECTOR3				m_pos;
	D3DXVECTOR3				m_rot;
	D3DXMATRIXA16			m_matWorld;

	IDisplayObject*			m_pParent;
	vector<IDisplayObject*> m_vecPChild;

public:
	IDisplayObject();
	virtual ~IDisplayObject();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
    virtual void Release() override;
	virtual void AddChild(IDisplayObject& val);

    D3DXVECTOR3		     GetPosition() const;
    void			     SetPosition(const D3DXVECTOR3& pos);
    D3DXVECTOR3		     GetRotation() const;
    const D3DXMATRIXA16& GetWorldMatrix() const;

    void UpdateChildren();
    void RenderChildren();
    void ReleaseChildren();
};

