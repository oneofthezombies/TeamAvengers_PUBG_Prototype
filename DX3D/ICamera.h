#pragma once
#include "BaseObject.h"

#define FP_DISTANCE -1.0f
#define FP_BASEPOSX 0.0f
#define FP_BASEPOSY 3.0f

#define TP_DISTANCE 10.0f
#define TP_BASEPOSX 2.0f
#define TP_BASEPOSY 8.0f

namespace CameraState
{
    enum CameraState
    {
        FIRSTPERSON = 1,
        THIRDPERSON = 3,
        TP2FP,
        FP2TP,
        KYUNCHAK
    };
}

class ICamera : public BaseObject
{
public:
    CameraState::CameraState     m_cameraState;
public://protected 으로 바꾸자
    D3DXVECTOR3		m_eye;
    D3DXVECTOR3		m_lookAt;
    D3DXVECTOR3		m_up;
    D3DXMATRIXA16	m_matView;
    D3DXMATRIXA16	m_matProj;

    float           m_basePosX;
    float			m_basePosY;
    float			m_distance;

    float			m_rotX;
    float			m_rotY;

    float           m_fovY;
    float           m_aspect;

    POINT			m_ptPrevMouse;
    POINT           m_ptContainer;



    //vector<D3DXVECTOR3> m_vecProjVert;
    //vector<D3DXVECTOR3> m_vecWorldVert;
    //vector<D3DXPLANE>	m_vecSixPlane;

    ICamera();
public:
    virtual ~ICamera() {}
    virtual void Init();
    virtual void Update();

    //virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    //void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }
    
    //functions needed for backspace currling
    //void SetProjVert();
    //void ChangeToWorldVert();
    //void SetSixPlane();
    //bool CheckSphere(BoundingSphere* sphere);

    void UpdateEye();
};

