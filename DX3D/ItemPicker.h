#pragma once

#include "BaseObject.h"
#include "Collider.h"

class PlayerAni;
class Item;

class ItemPickerCollisionListener : public ICollisionListener
{
public:
    ItemPickerCollisionListener(BaseObject& owner);
    virtual ~ItemPickerCollisionListener() = default;

    virtual void OnCollisionEnter(const ColliderBase & other) override;
    virtual void OnCollisionExit(const ColliderBase & other) override;
    virtual void OnCollisionStay(const ColliderBase & other) override;
};

class ItemPicker : public BaseObject
{
private:
    PlayerAni* m_pOwner;

    BoxCollider*                 m_pBoxCollider;
    ItemPickerCollisionListener* m_pCollisionListener;

public:
    ItemPicker(PlayerAni& owner);
    virtual ~ItemPicker();

    void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);
    void Update(vector<Item*>& OutItems, const D3DXMATRIXA16& transform);

    static ItemPicker* Create(PlayerAni& owner, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);
};