#include "stdafx.h"
#include "IAction.h"
#include "IActionObject.h"


IAction::IAction(float _totalTime)
{
	m_pTarget = NULL;
	m_pActionDelegate = NULL;
	m_isFinish = false;
	m_currentTime = 0;
	m_totalTime = _totalTime;
}


IAction::~IAction()
{
}

void IAction::Reset()
{
	m_isFinish = false;
	m_currentTime = 0;
}

void IAction::Update()
{
	if (m_isFinish)
		return;

	m_currentTime += g_pTimeManager->GetDeltaTime();

	if (m_currentTime < m_totalTime)
	{
		UpdateAction();
	}
	else
	{
		if (m_pActionDelegate)
			m_pActionDelegate->OnFinishAction();
	}
}


