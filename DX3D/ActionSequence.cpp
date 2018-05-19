#include "stdafx.h"
#include "ActionSequence.h"


ActionSequence::ActionSequence()
{
}


ActionSequence::~ActionSequence()
{
}

void ActionSequence::Release()
{
	for (auto action : m_vecActionList)
		action->Release();

	BaseObject::Release();
}

void ActionSequence::Update()
{
	if (m_isFinish)
		return;

	m_vecActionList[m_index]->Update();
}


void ActionSequence::Reset()
{
	m_isFinish = false;
	m_index = 0;
	m_vecActionList[m_index]->Reset();
}


void ActionSequence::SetTarget(IActionObject * _target)
{
	m_pTarget = _target;
	for (auto & action : m_vecActionList)
		action->SetTarget(m_pTarget);
}


void ActionSequence::OnFinishAction()
{
	m_index++;
	if (m_index >= m_vecActionList.size())
	{
		m_isFinish = true;
		if (m_pActionDelegate)
			m_pActionDelegate->OnFinishAction();
	}
	else
		m_vecActionList[m_index]->Reset();
}

void ActionSequence::AddAction(IAction* _action)
{
	_action->SetDelegate(this);
	m_vecActionList.push_back(_action);
}