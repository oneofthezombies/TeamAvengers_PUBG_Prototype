#pragma once
#include "IAction.h"

class ActionSequence : public IAction, public IActionDelegate
{
private:
	vector<IAction*> m_vecActionList;
	size_t m_index;

public:
	ActionSequence();
	~ActionSequence();

	//BaseObject
	virtual void Release() override;

	//IAction
	virtual void Update() override;
	virtual void Reset() override;
	virtual void SetTarget(IActionObject* _target) override;

	//IActionDelegate
	virtual void OnFinishAction() override;

	void AddAction(IAction* _action);
};

