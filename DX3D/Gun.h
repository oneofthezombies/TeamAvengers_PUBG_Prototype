#pragma once
#include "Item.h"

class Bullet;
class MuzzleFlash;

class Gun : public Item
{
private:
	GUN_TAG          m_gunTag;
    LPD3DXMESH       m_pGunMesh;            //총을 그려주기 위한 메쉬
	vector<Bullet*>  m_vecPBullet;          //총알 담을 벡터
	const int        m_maxBullet;           //최대 장전 개수

	const int        m_bulletFireCoolTime; 
	int              m_bulletFireCoolDown; //총알 발사는 지정된 쿨타임 시간이 지나야 다시 발사가능

    bool             m_canChangeBurstMode; //연발이 가능한 총인지

	const float      m_velocity;           //이동을 위한 속력
	const float      m_scale;
	float            m_rotY;
	
	D3DXMATRIXA16    m_matS;
	D3DXMATRIXA16    m_matRotY;
	D3DXMATRIXA16    m_matT;

    MuzzleFlash* m_muzzleFlash;

public:
	Gun(GUN_TAG gunTag, bool canChangeBurstMode, int bulletNum, int bulletFireCoolTime, float velocity, float scale, float rotY);
	virtual ~Gun();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

    size_t GetBulletNum();
    int GetMaxNumBullet();
    int GetNeedBullet();
    GUN_TAG GetGunTag();
    bool GetCanChangeBurstMode();

	void Fire(const D3DXVECTOR3& dir); //총쏘기
	void Load(Bullet* bullet); //장전
    void SyncRot(float rotY);   //캐릭터 위치에 맞게 고정. (해당 주전자 로컬좌표 때문에 -D3DXToRadian(90)해줌)

    /* 디버그 */
    void ShowBulletNumForDebug();
    string GunTagToStrForDebug(GUN_TAG gunTag);
};

