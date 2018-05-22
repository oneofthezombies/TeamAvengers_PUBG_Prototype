#pragma once
#include "Item.h"

class Bullet : public Item
{
private:
	LPD3DXMESH    m_pBulletMesh;  //총알을 출력하기 위한 메쉬
	bool          m_isFire;       //총알이 발사되었는지
	bool          m_isDie;        //경계범위를 벗어나거나 어딘가 충돌할 때 죽음

	const float   m_velocity;     //이동을 위한 속력
	const float   m_scale;
	//D3DXVECTOR3 m_pos;          //IDisplayObject에 있음

	D3DXMATRIXA16 m_matS;
	D3DXMATRIXA16 m_matT;
	 
public:
	Bullet(float scale, float velocity);
	~Bullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	bool  GetIsFire() const { return m_isFire; }
	void  SetIsFire(const bool isFire){ m_isFire = isFire; }
	float GetVelocity() const { return m_velocity; }
	bool  GetIsDie() const { return m_isDie; }

	bool IsInBorderArea(); //경계구역 안에 있는지 체크
};