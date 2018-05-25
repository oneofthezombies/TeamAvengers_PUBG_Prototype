#include "stdafx.h"
#include "UIInventory.h"
#include "Item.h"
#include "UIText.h"
#include "PlayerAni.h"
#include "SceneShotting.h"

UIInventory::UIInventory()
    : UIImage()
{
}

UIInventory::~UIInventory()
{
}

void UIInventory::Init()
{
    g_pUIManager->RegisterUIObject(*this);

    SetTexture("resources/images/black_1280_720_70.png");
    SetSize(D3DXVECTOR2(1280.0f, 720.f));
}

void UIInventory::Update(Item*& OutPPicked, map<ITEM_TAG, vector<Item*>>& inventory, vector<Item*>& pickables)
{
    ClearChildren();

    if (OutPPicked)
    {
        if (g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
        {
            UIText* picked = new UIText;
            picked->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageDescription));
            picked->SetText(OutPPicked->GetName().c_str());
            AddChild(*picked);
            const POINT pos = g_pKeyManager->GetCurrentMousePos();
            picked->SetPosition(D3DXVECTOR3(static_cast<float>(pos.x) - 100.0f, static_cast<float>(pos.y) - 25.0f, 0.0f));
            picked->SetSize(D3DXVECTOR2(200.0f, 50.0f));
        }
        else
        {
            const POINT pos = g_pKeyManager->GetCurrentMousePos();
            if (pos.x > 350 && pos.x < 550)
            {
                // push to inventory
                PlayerAni* o = static_cast<PlayerAni*>(GetAttachedObject());
                o->Pick(*OutPPicked);
                //o->PutItemInInventory(OutPPicked);

                IScene* s = g_pCurrentScene;
                SceneShotting* ss = static_cast<SceneShotting*>(s);
                ss->RemoveItemPointer(*OutPPicked);

                OutPPicked = nullptr;
            }
            else
            {
                // drop to ground

            }
        }
    }

    Debug->AddText("num of pickables : " + to_string(pickables.size()) + '\n');

    vector<RECT> rects;
    for (int i = 0; i < pickables.size(); ++i)
    {
        UIText* pickable = new UIText;
        pickable->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageDescription));
        pickable->SetText(pickables[i]->GetName().c_str());
        AddChild(*pickable);
        pickable->SetPosition(D3DXVECTOR3(100.0f, 50.0f + 50.0f * static_cast<float>(i), 0.0f));
        pickable->SetSize(D3DXVECTOR2(200.0f, 50.0f));
        rects.emplace_back(RECT{});
        SetRect(&rects.back(), 100, 50 + 50 * i, 300, 100 + 50 * i);
    }

    if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < pickables.size(); ++i)
        {
            if (PtInRect(&rects[i], g_pKeyManager->GetCurrentMousePos()))
            {
                OutPPicked = pickables[i];
            }
        }
    }

    int i = 0;
    for (auto& kv : inventory)
    {
        for (auto it : kv.second)
        {
            UIText* item = new UIText;
            item->SetFont(g_pFontManager->GetFont(Font::kInteractionMessageDescription));
            item->SetText(it->GetName().c_str());
            AddChild(*item);
            item->SetPosition(D3DXVECTOR3(350.0f, 50.0f + 50.0f * static_cast<float>(i), 0.0f));
            item->SetSize(D3DXVECTOR2(200.0f, 50.0f));
            rects.emplace_back(RECT{});
            SetRect(&rects.back(), 350, 50 + 50 * i, 550, 100 + 50 * i);
            ++i;
        }
    }
}

UIInventory* UIInventory::Create()
{
    UIInventory* ret = new UIInventory;
    ret->Init();
    return ret;
}
