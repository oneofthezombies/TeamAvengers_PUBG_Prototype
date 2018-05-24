#pragma once

#include "UIImage.h"

class Item;

class UIInventory : public UIImage
{
private:

public:
    UIInventory();
    virtual ~UIInventory();

    void Init();
    void Update(Item*& OutPPicked, map<ITEM_TAG, vector<Item*>>& inventory, vector<Item*>& pickables);

    static UIInventory* Create();
};