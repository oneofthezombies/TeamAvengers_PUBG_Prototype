#pragma once
#include "Item.h"

/* ���� */
class Bullet;
class Pistol : public Item
{
private:
	LPD3DXMESH       m_pGunMesh;            //���� �׷��ֱ� ���� �޽�
	vector<Bullet*>  m_vecPBullet;          //�Ѿ� ���� ����
	const int        m_maxBullet;           //�ִ� ���� ����

	const int        m_bulletFireCoolTime; 
	int              m_bulletFireCoolDown; //�Ѿ� �߻�� ������ ��Ÿ�� �ð��� ������ �ٽ� �߻簡��

	const float      m_velocity;           //�̵��� ���� �ӷ�
	const float      m_scale;
	float      m_rotY;
	//D3DXVECTOR3    m_pos;                //IDisplayObject�� ����
	
	D3DXMATRIXA16    m_matS;
	D3DXMATRIXA16    m_matRotY;
	D3DXMATRIXA16    m_matT;

public:
	Pistol(int bulletNum, int bulletFireCoolTime, float velocity, float scale, float rotY);
	virtual ~Pistol();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	size_t GetBulletNum() { return m_vecPBullet.size(); }
	void ShowBulletNumForDebug();
	int GetNeedBullet() { return m_maxBullet - GetBulletNum(); }

	void Fire(); //�ѽ��
	void Load(Bullet* bullet); //����
    void SyncRot(float rotY);   //ĳ���� ��ġ�� �°� ����. (�ش� ������ ������ǥ ������ -D3DXToRadian(90)����)
};
