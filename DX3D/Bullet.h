#pragma once
#include "Item.h"
#include "Collider.h"

class BulletCollider;
class BulletCollisionListener;

class Bullet : public Item
{
private:
	GUN_TAG       m_bulletFor;    //어느 총을 위한 총알인지
	LPD3DXMESH    m_pBulletMesh;  //총알을 출력하기 위한 메쉬
	bool          m_isFire;       //총알이 발사되었는지
	bool          m_isDie;        //경계범위를 벗어나거나 어딘가 충돌할 때 죽음

	const float   m_velocity;     //이동을 위한 속력
    D3DXVECTOR3   m_dir;
	const float   m_scale;

	D3DXMATRIXA16 m_matS;
	D3DXMATRIXA16 m_matT;

    BoxCollider* m_pBoxCollider;


public:
	Bullet(GUN_TAG bulletFor, float scale, float velocity);
	~Bullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

    bool  GetIsFire() const;
    void  SetIsFire(const bool isFire);
    float GetVelocity() const;
    bool  GetIsDie() const;
    GUN_TAG  GetBulletFor();
	bool IsBulletForThisGun(GUN_TAG gunTag);

	bool IsInBorderArea(); //경계구역 안에 있는지 체크

    void SetDirection(const D3DXVECTOR3& val);
};
