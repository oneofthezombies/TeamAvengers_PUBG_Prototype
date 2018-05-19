#pragma once

#include "BaseObject.h"

class IActionObject;

class IActionDelegate
{
public:
	virtual void OnFinishAction() = 0;
};

class IAction : public BaseObject
{
protected:
	IActionObject *		m_pTarget;
	IActionDelegate*	m_pActionDelegate;
	bool				m_isFinish;
	float				m_currentTime;
	float				m_totalTime;

public:
	IAction(float _totalTime = 0);
	virtual ~IAction();

	virtual void Update();
	virtual void UpdateAction() {}
	virtual void Reset();
	virtual void SetTarget(IActionObject* pTarget) { m_pTarget = pTarget; }
	void SetDelegate(IActionDelegate* pActionDelegate) { m_pActionDelegate = pActionDelegate; }
	float GetTimeRate() { return m_currentTime / m_totalTime; }
};

#include "ActionMoveTo.h"
#include "ActionSequence.h"
#include "ActionRepeat.h"