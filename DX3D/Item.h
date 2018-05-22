#pragma once
#include "IDisplayObject.h"

class Item : public IDisplayObject
{
protected:
	ITEM_TAG   m_tag;
	ITEM_STATE m_state;
	string     m_name;
	string     m_desc;

public:
	Item(ITEM_TAG tag,string name, string desc);
	~Item();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	ITEM_TAG GetItemTag() { return m_tag; }
	ITEM_STATE GetItemState() { return m_state; }
	void SetItemState(ITEM_STATE state) { m_state = state; }
};

