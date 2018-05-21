#pragma once
#include "BaseObject.h"
class ICamera : public BaseObject
{
protected:
    enum CameraState
    {
        FIRSTPERSON=1,
        THIRDPERSON=3
    };
    CameraState     m_cameraState;

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

    bool			m_isLbuttonDown;
    bool			m_isRbuttonDown;
    POINT			m_ptPrevMouse;
    //D3DXVECTOR3*	m_pTarget;

    //vector<D3DXVECTOR3> m_vecProjVert;
    //vector<D3DXVECTOR3> m_vecWorldVert;
    //vector<D3DXPLANE>	m_vecSixPlane;

    ICamera() {}
public:
    virtual ~ICamera() {}
    virtual void Init() = 0;
    virtual void Update() = 0;

    //void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }
    
    //functions needed for backspace currling
    //void SetProjVert();
    //void ChangeToWorldVert();
    //void SetSixPlane();
    //bool CheckSphere(BoundingSphere* sphere);
};

