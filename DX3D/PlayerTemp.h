#pragma once
#include "IDisplayObject.h"
#include "Item.h"

//임시플레이어
class Pistol;
class Bullet;
class PlayerTemp : public IDisplayObject
{
private:
	LPD3DXMESH                   m_pPlayerMesh; //임시플레이어를 그려주기 위한 메쉬
	
	//TODO: multimap으로 변경할 것
	map<ITEM_TAG, vector<Item*>> m_mapInventory;
	Pistol*                      m_pPistol;     //장착중인 총

	float                        m_velocity;
	bool                         m_isRun;

	D3DXMATRIXA16                m_matT;
	D3DXMATRIXA16                m_matRotY;

public:
	PlayerTemp();
	~PlayerTemp();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	size_t GetInventorySize() { return m_mapInventory.size(); }
	void PutItemInInventory(Item* item);
	void ShowInventoryForDebug();

	/* 키 입력 관련 함수로 분리*/
	void KeyMove();    //이동
	void KeyMount();   //장착
	void KeyUnmount(); //장착해제
	void KeyLoad();    //총 장전
	void KeyFire();    //총 쏘기
};

