#pragma once
#include "IDisplayObject.h"

//임시플레이어
class Pistol;
class PlayerTemp : public IDisplayObject
{
private:
	LPD3DXMESH              m_pPlayerMesh; //임시플레이어를 그려주기 위한 메쉬
	Pistol*                 m_pPistol;        //총을 소유하고 있다

	float                   m_velocity;
	bool                    m_isRun;

	D3DXMATRIXA16           m_matT;
	D3DXMATRIXA16           m_matRotY;

public:
	PlayerTemp();
	~PlayerTemp();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

