#pragma once
#include "IDisplayObject.h"

class Item : public IDisplayObject
{
protected:
	ITEM_TAG     m_tag;
	ITEM_STATE   m_state;
	string       m_name;
	string       m_desc;

    BoxCollider* m_pBoxCollider;
    LPD3DXMESH   m_pMesh;

public:
	Item(ITEM_TAG tag,string name, string desc);
	~Item();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	ITEM_TAG GetItemTag() { return m_tag; }
    void SetItemState(ITEM_STATE state) { m_state = state; }
	ITEM_STATE GetItemState() { return m_state; }

    const string& GetName() const;

    const D3DMATERIAL9& GetMaterialByItemTag();
    bool IsVisible();
};

