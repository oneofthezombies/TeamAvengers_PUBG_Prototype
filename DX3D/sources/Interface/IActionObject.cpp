#include "stdafx.h"
#include "IActionObject.h"
#include "IAction.h"

IActionObject::IActionObject()
{
	pAction = NULL;
}


IActionObject::~IActionObject()
{
	ReleaseAction();
}

void IActionObject::RunAction(IAction * _action)
{
	ReleaseAction();
	pAction = _action;
	pAction->SetTarget(this);
}

void IActionObject::UpdateAction()
{
	if (pAction)
	{
		pAction->Update();
	}
}

void IActionObject::ReleaseAction()
{
	if (pAction)
		pAction->Release();
}
