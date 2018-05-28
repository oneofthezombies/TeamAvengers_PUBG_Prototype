#pragma once
#include "IDisplayObject.h"
#include "PlayerParts.h"
#include "Item.h"
#include "Collider.h"

class PlayerParts;
class Gun;
class Bullet;
class BoxCollider;
class ItemPicker;
class UIInventory;

class PlayerAniCollisionListener : public ICollisionListener
{
private:
    string gameOverText;

public:
	PlayerAniCollisionListener(BaseObject& owner);
	virtual ~PlayerAniCollisionListener() = default;

	virtual void OnCollisionEnter(const ColliderBase& other) override;
	virtual void OnCollisionExit(const ColliderBase& other) override;
	virtual void OnCollisionStay(const ColliderBase& other) override;
};

class PlayerAni : public IDisplayObject
{
private:
    PlayerParts*    m_pRootParts;
    bool			m_isTurnedOnLight;

    D3DXVECTOR3		m_deltaPos;
    D3DXVECTOR3		m_deltaRot;
    D3DXVECTOR3		m_forward;

    D3DXVECTOR3		m_test1;
    D3DXVECTOR3     m_dir;
    D3DXVECTOR3		m_right;
    D3DXVECTOR3     m_vRotForAlt;

    bool			m_isMoving;
    float			m_moveSpeed;
    float			m_currMoveSpeedRate;
    float			m_rotationSpeed;

    bool			m_isJumping;
    float			m_jumpPower;
    float			m_gravity;
    float			m_currGravity;

    float			m_maxStepHeight;

    bool            m_isRunnig;
    bool            m_isLive;

    FIRE_MODE       m_fireMode;
	Gun*            m_pGun;      //Gun that in hand
	map<ITEM_TAG, vector<Item*>> m_mapInventory;
	map<GUN_TAG, Gun*>           m_mapGuns;

	BoxCollider*			     m_pBoxCollider;
    PlayerAniCollisionListener*  m_pCollisionListener;

    ItemPicker*  m_pItemPicker;
    UIInventory* m_pUIInventory;
    Item*        m_pPicked;

    bool m_isGameOver;

public:
    PlayerAni();
    ~PlayerAni();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    void UpdatePosition();
    void CreateAllParts();
    void CreateParts(PlayerParts* &pParts, IDisplayObject* pParent, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans,
                     vector<vector<int>> &vecUV,  PartTag tag);
    
    void DrawGunInOut();  
    void RunAndWalk();
    void DiedAni();

    PlayerParts* GetChild(int index);
    size_t GetInventorySize();
    size_t GetGunsNum();

	void PutItemInInventory(Item* item);
	void PutGunInEquip(Gun* gun);

	/* For Key Input*/
	void KeyMove();
	void KeyInHand(GUN_TAG gunTag);
	void KeyOutHand();
	void KeyLoad();
	void KeyFire(const D3DXVECTOR3& dir);
	void KeyChangeGun(GUN_TAG gunTag);
    void KeyChangeFireMode();

    void UpdateRotation();
    void UpdateDirection();
    void UpdateGunInHandPosition();
    void UpdateGunInEquipPosition();

    void ShowInventory(const D3DXMATRIX& transform);
    bool IsShowingInventory();
    void Pick(Item& item);

    /* For Debug */
    void ShowInventoryForDebug();
    void ShowFireModeForDebug();
    void ShowItemStateForDebug(ITEM_STATE itemState);

    void SetIsGameOver(const bool val);
    bool IsGameOver() const;

public:
    vector<vector<int>> uvBody = {
    { 32, 32, 32, 20, 40, 20, 40, 32 },	// back
    { 20, 32, 20, 20, 28, 20, 28, 32 },	// front
    { 28, 32, 28, 20, 32, 20, 32, 32 },	// left
    { 16, 32, 16, 20, 20, 20, 20, 32 },	// right
    { 20, 20, 20, 16, 28, 16, 28, 20 },	// up
    { 28, 16, 28, 20, 36, 20, 36, 16 }	// down
    };

    vector<vector<int>> uvHead = {
    { 24, 16, 24, 8, 32, 8, 32, 16 },	
    { 8, 16, 8, 8, 16, 8, 16, 16 },		
    { 16, 16, 16, 8, 24, 8, 24, 16 },	
    { 0, 16, 0, 8, 8, 8, 8, 16 },		
    { 8, 8, 8, 0, 16, 0, 16, 8 },		
    { 16, 0, 16, 8, 24, 8, 24, 0 }		
    };

    vector<vector<int>> uvLArm = {
    { 44, 32, 44, 20, 48, 20, 48, 32 },	
    { 52, 32, 52, 20, 56, 20, 56, 32 },	
    { 40, 32, 40, 20, 44, 20, 44, 32 },	
    { 48, 32, 48, 20, 52, 20, 52, 32 },	
    { 44, 20, 44, 16, 48, 16, 48, 20 },	
    { 48, 16, 48, 20, 52, 20, 52, 16 }	
    };

    vector<vector<int>> uvRArm = {
    { 48, 32, 48, 20, 44, 20, 44, 32 },	
    { 56, 32, 56, 20, 52, 20, 52, 32 },	
    { 48, 32, 48, 20, 52, 20, 52, 32 },	
    { 40, 32, 40, 20, 44, 20, 44, 32 },	
    { 48, 20, 48, 16, 44, 16, 44, 20 },	
    { 52, 16, 52, 20, 48, 20, 48, 16 }	
    };

    vector<vector<int>> uvLLeg = {
    { 12, 32, 12, 20, 16, 20, 16, 32 },	
    { 4, 32, 4, 20, 8, 20, 8, 32 },		
    { 8, 32, 8, 20, 12, 20, 12, 32 },	
    { 0, 32, 0, 20, 4, 20, 4, 32 },		
    { 4, 20, 4, 16, 8, 16, 8, 20 },		
    { 8, 16, 8, 20, 12, 20, 12, 16 }	
    };

    vector<vector<int>> uvRLeg = {
    { 16, 32, 16, 20, 12, 20, 12, 32 },	
    { 8, 32, 8, 20, 4, 20, 4, 32 },		
    { 4, 32, 4, 20, 0, 20, 0, 32 },		
    { 12, 32, 12, 20, 8, 20, 8, 32 },	
    { 8, 20, 8, 16, 4, 16, 4, 20 },		
    { 12, 16, 12, 20, 8, 20, 8, 16 }	
    };
};

