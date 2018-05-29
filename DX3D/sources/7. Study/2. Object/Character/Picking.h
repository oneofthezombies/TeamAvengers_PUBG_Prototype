#pragma once
#include "IDisplayObject.h"
class Picking :
	public IDisplayObject
{
private:
	LPD3DXMESH				m_pSphere;
	vector<BoundingSphere*> m_vecBoundary;

public:
	Picking();
	~Picking();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

