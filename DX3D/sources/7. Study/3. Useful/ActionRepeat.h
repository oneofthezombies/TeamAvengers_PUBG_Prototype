#pragma once
#include "IAction.h"

#define DONT_STOP -1

class ActionRepeat : public IAction, public IActionDelegate
{
private:
	IAction *	m_pAction;
	int			m_currRepeatCnt;
	int			m_totalRepeatCnt;

public:
	ActionRepeat(IAction* pAction = NULL, int totalRepeatCnt = DONT_STOP);
	~ActionRepeat();

	//BaseObject
	virtual void Release() override;

	//IAction
	virtual void Update() override;
	virtual void Reset() override;
	virtual void SetTarget(IActionObject* _target) override;

	//IActionDelegate
	virtual void OnFinishAction() override;

};

