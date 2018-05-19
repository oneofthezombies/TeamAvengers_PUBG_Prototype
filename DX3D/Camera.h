#pragma once

#define g_pCamera Camera::GetInstance()

class Camera
{
	SINGLETON(Camera)
private:
	D3DXVECTOR3		m_eye;
	D3DXVECTOR3		m_lookAt;
	D3DXVECTOR3		m_up;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;
	float			m_basePosY;
	float			m_distance;
	float			m_rotX;
	float			m_rotY;
	bool			m_isLbuttonDown;
	POINT			m_ptPrevMouse;
	D3DXVECTOR3*	m_pTarget;

	vector<D3DXVECTOR3> m_vecProjVert;
	vector<D3DXVECTOR3> m_vecWorldVert;
	vector<D3DXPLANE>	m_vecSixPlane;

public:
	void Init();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }


	void SetProjVert();
	void ChangeToWorldVert();
	void SetSixPlane();
	bool CheckSphere(BoundingSphere* sphere);
};

