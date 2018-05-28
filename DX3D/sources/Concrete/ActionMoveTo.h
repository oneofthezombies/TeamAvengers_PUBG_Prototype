#pragma once
#include "IAction.h"

class ActionMoveTo : public IAction
{
private:
	D3DXVECTOR3 m_from;
	D3DXVECTOR3 m_to;

public:
	ActionMoveTo(float _totalTime, D3DXVECTOR3 _to);
	virtual ~ActionMoveTo();
	
	//IAction
	virtual void UpdateAction() override;
	virtual void Reset() override;
};

