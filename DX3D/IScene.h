#pragma once
#include "BaseObject.h"
#include "IDisplayObject.h"
class IDisplayObject;

class IScene : public BaseObject
{
protected:
	set<IDisplayObject*> m_simpleDisplayList;

	IScene() {}

public:
	virtual ~IScene() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

	void AddSimpleDisplayObj(IDisplayObject* p)
	{m_simpleDisplayList.insert(p);}
	void RemoveSimpleDisplayObj(IDisplayObject* p)
	{m_simpleDisplayList.erase(p);}
	void OnUpdateIScene() 
	{ for (auto p : m_simpleDisplayList) 
		SAFE_UPDATE(p); }
	void OnRenderIScene()
	{for (auto p : m_simpleDisplayList) 
		SAFE_RENDER(p);	}
	void OnDestructIScene()
	{for (auto p : m_simpleDisplayList) 
		SAFE_RELEASE(p);}
};

