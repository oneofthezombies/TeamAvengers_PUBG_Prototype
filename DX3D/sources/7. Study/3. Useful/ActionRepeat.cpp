#include "stdafx.h"
#include "ActionRepeat.h"

ActionRepeat::ActionRepeat(IAction* pAction, int totalRepeatCnt)
{
	m_pAction = pAction;
	m_pAction->SetDelegate(this);
	m_totalRepeatCnt = totalRepeatCnt;
}


ActionRepeat::~ActionRepeat()
{
}

void ActionRepeat::Release()
{
	SAFE_RELEASE(m_pAction);

	BaseObject::Release();
}

void ActionRepeat::Update()
{
	if (m_isFinish)
		return;

	m_pAction->Update();
}


void ActionRepeat::Reset()
{
	m_isFinish = false;
	m_currRepeatCnt = 0;
	if (m_pAction) m_pAction->Reset();
}

void ActionRepeat::SetTarget(IActionObject * _target)
{
	m_pTarget = _target;
	m_pAction->SetTarget(m_pTarget);
}

void ActionRepeat::OnFinishAction()
{
	m_pAction->Reset();

	if (m_totalRepeatCnt == DONT_STOP) return;

	m_currRepeatCnt++;
	if (m_currRepeatCnt >= m_totalRepeatCnt)
		m_isFinish = true;
}

