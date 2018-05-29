#pragma once

#include "UIImage.h"

class Item;
class Gun;

class UIInventory : public UIImage
{
private:

public:
    UIInventory();
    virtual ~UIInventory();

    void Init();
    void Update(Item*& OutPPicked, map<ITEM_TAG, vector<Item*>>& inventory, vector<Item*>& pickables, map<GUN_TAG, Gun*>& equipment);

    void RegisterCoreTexts();

    static UIInventory* Create();
};