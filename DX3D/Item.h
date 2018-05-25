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

    ITEM_TAG GetItemTag();
    void SetItemState(ITEM_STATE state);
    ITEM_STATE GetItemState();
    const string& GetName() const;

    const D3DMATERIAL9& GetMaterialByItemTag();
    bool IsVisible();
};

