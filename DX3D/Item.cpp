#include "stdafx.h"
#include "Item.h"


Item::Item(ITEM_TAG tag, string name, string desc)
	: m_tag(tag)
	, m_name(name)
	, m_desc(desc)
{
	m_state = ITEM_STATE::Dropped;
}

Item::~Item()
{
}

void Item::Init()
{
}

void Item::Update()
{
}

void Item::Render()
{
}
