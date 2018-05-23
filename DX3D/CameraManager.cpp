#include "stdafx.h"
#include "CameraManager.h"
#include "ICamera.h"
#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"


CameraManager::CameraManager()
    : m_pTargetDir(nullptr)
    , m_pTargetPos(nullptr)
{
    m_pCurrentCamera = NULL;
}


CameraManager::~CameraManager()
{
}

void CameraManager::SetCurrentCamera(int cameraState)
{
    m_pCurrentCamera = m_mapList[cameraState];
    
    //이거 가장 자식의 init하고 싶은데 어떻게 해야 합니까?
    //m_pCurrentCamera->Init(); 
    //일단 switch 문으로 해결
    switch (m_pCurrentCamera->m_cameraState)
    {
    case CameraState::FIRSTPERSON:
        static_cast<FirstPersonCamera*>(m_pCurrentCamera)->Init();
        break;
    case CameraState::THIRDPERSON :
        static_cast<ThirdPersonCamera*>(m_pCurrentCamera)->Init();
        break;
    case CameraState::FP2TP :
        static_cast<CameraFPToTP*>(m_pCurrentCamera)->Init();
        break;
    case CameraState::TP2FP :
        static_cast<CameraTPToFP*>(m_pCurrentCamera)->Init();
        break;
    case CameraState::KYUNCHAK:
        static_cast<CameraKyunChak*>(m_pCurrentCamera)->Init();
        break;
    }
    
}

void CameraManager::Init()
{
    ICamera* tempContainer;
    //FP 와 TP 생성 + Map 에 추가
    tempContainer = new FirstPersonCamera();
    AddCamera(CameraState::FIRSTPERSON, tempContainer);
    tempContainer = new ThirdPersonCamera();
    AddCamera(CameraState::THIRDPERSON, tempContainer);
    
    //FP와 TP를 lerp로 치환해 주는 class 생성
    tempContainer = new CameraFPToTP();
    AddCamera(CameraState::FP2TP, tempContainer);
    tempContainer = new CameraTPToFP();
    AddCamera(CameraState::TP2FP, tempContainer);

    tempContainer = new CameraKyunChak();
    AddCamera(CameraState::KYUNCHAK, tempContainer);

    //currCamera 설정 + init()
    SetCurrentCamera(CameraState::THIRDPERSON);
}

void CameraManager::Destroy()
{
    for (auto& c : m_mapList)
    {
        SAFE_RELEASE(c.second);
    }
}

void CameraManager::Update()
{
    const float dt = g_pTimeManager->GetDeltaTime();

    if (g_pKeyManager->IsOnceKeyDown('V'))
    {
        if (m_pCurrentCamera->m_cameraState == CameraState::THIRDPERSON)
        {
            g_pCameraManager->SetCurrentCamera(CameraState::TP2FP);
        }
        else
        {
            g_pCameraManager->SetCurrentCamera(CameraState::FP2TP);
        }
    }
    SAFE_UPDATE(m_pCurrentCamera);
}

//void CameraManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    SAFE_WNDPROC(m_pCurrentCamera);
//}

void CameraManager::SetTarget(D3DXVECTOR3& pos, D3DXVECTOR3& dir)
{
    m_pTargetPos = &pos;
    m_pTargetDir = &dir;
}

D3DXVECTOR3* CameraManager::GetTargetPos() const
{
    return m_pTargetPos;
}

D3DXVECTOR3* CameraManager::GetTargetDir() const
{
    return m_pTargetDir;
}
