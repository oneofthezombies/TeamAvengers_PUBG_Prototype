#pragma once
#include "IDisplayObject.h"

/* 권총 */
class Bullet;
class Pistol : public IDisplayObject
{
private:
	LPD3DXMESH       m_pGunMesh;           //총을 그려주기 위한 메쉬
	vector<Bullet*>  m_vecBullet;          //총알 담을 벡터
	const int        m_bulletNum;          //최대 장전 개수

	const int        m_bulletFireCoolTime; 
	int              m_bulletFireCoolDown; //총알 발사는 지정된 쿨타임 시간이 지나야 다시 발사가능

	const float      m_velocity;           //이동을 위한 속력
	const float      m_scale;
	const float      m_rotY;
	//D3DXVECTOR3    m_pos;                //IDisplayObject에 있음
	
	D3DXMATRIXA16    m_matS;
	D3DXMATRIXA16    m_matRotY;
	D3DXMATRIXA16    m_matT;

public:
	Pistol(int bulletNum, int bulletFireCoolTime, float velocity, float scale, float rotY);
	~Pistol();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Fire(); //총쏘기
	void Load(); //장전
};

