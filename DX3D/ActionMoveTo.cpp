#include "stdafx.h"
#include "ActionMoveTo.h"
#include "IActionObject.h"

ActionMoveTo::ActionMoveTo(float _totalTime, D3DXVECTOR3 _to)
	:IAction(_totalTime)
{
	m_to = _to;
}


ActionMoveTo::~ActionMoveTo()
{
}

void ActionMoveTo::Reset()
{
	IAction::Reset();

	m_from = m_pTarget->GetPosition();
}

void ActionMoveTo::UpdateAction()
{
	D3DXVECTOR3 pos;
	D3DXVec3Lerp(&pos, &m_from, &m_to, GetTimeRate());
	m_pTarget->SetPosition(&pos);
}


