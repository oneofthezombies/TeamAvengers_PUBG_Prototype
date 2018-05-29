#pragma once
#include "IDisplayObject.h"
#include "IUnitObject.h"

class AseObject;

class AseCharacter : public IUnitObject
{
private:
	ASE_SCENE m_aseScene;	//tick을 저장
	AseObject * m_pCurrObj;
	AseObject * m_pStandObj;	//일어나있는 모션 저장
	AseObject * m_pRunObj;		//뛰는 모션 저장

public:
	AseCharacter();
	~AseCharacter();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Load(OUT AseObject* &rootObj, const char* fullPath);
	void SetCurrentObject(AseObject* pObj) { m_pCurrObj = pObj; }
};

