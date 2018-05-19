#pragma once
#include "IDisplayObject.h"

class IAction;

class IActionObject : public IDisplayObject
{
protected:
	IAction* pAction;

public:
	IActionObject();
	virtual ~IActionObject();
	
	void RunAction(IAction* _action);
	void UpdateAction();
	void ReleaseAction();
};

