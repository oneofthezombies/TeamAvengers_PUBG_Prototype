#include "stdafx.h"
#include "ThirdPersonCamera.h"
#include "Ray.h"


ThirdPersonCamera::ThirdPersonCamera()
    :ICamera()
    , m_pCamBackCheckingRay(nullptr)
{
    m_cameraState = CameraState::THIRDPERSON;
    m_distance = TP_DISTANCE;
    m_basePosX = TP_BASEPOSX;
    m_basePosY = TP_BASEPOSY;
    m_fovY = D3DX_PI *(80.0f / 180.0f);    //80 Degrees TP sight
    m_pCamBackCheckingRay = new Ray();
}

ThirdPersonCamera::~ThirdPersonCamera()
{
    SAFE_DELETE(m_pCamBackCheckingRay);
}

void ThirdPersonCamera::Init()
{
    
    ICamera::Init();
}

void ThirdPersonCamera::Update()
{
    //ALTkey를 누르면 주변을 볼 수 있는 기능
    m_isALTbuttonStay = g_pKeyManager->IsStayKeyDown(VK_MENU);//Alt기능을 Icamera update에 한번더 쓰기 때문에 이렇게 넣었습니다.
    //if (m_isALTbuttonStay)
    //{
    //}
    //else//alt를 누르지 않게 되면 캐릭터가 바라보고 있는 rotation 으로 초기화
    {
        if (m_pTargetRot)
        {
            m_rotX = m_pTargetRot->x;
            m_rotY = m_pTargetRot->y;
        }
        else
        {
            m_rotX = m_rotY = 0.0f;
        }
    }

    //견착하는 부분은 3인칭에서만 있기에
    if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
        g_pCameraManager->SetCurrentCamera(CameraState::KYUNCHAK);

    //Ray 카메라 ray를 뒤로 쏘아서 카메라 m_distance를 조정하는 부분
    //CamBackDistResizeing();

    ICamera::Update();
}

void ThirdPersonCamera::CamBackDistResizeing()
{
    D3DXVECTOR3 camBackDir = m_eye - m_lookAt;      //방향을 알아냄
    D3DXVec3Normalize(&camBackDir, &camBackDir);    //단위화
    //ray의 pos를 player의 distance와 같게, 쏘는 방향은 카메라 뒤쪽으로
    m_pCamBackCheckingRay->SetRay(m_eyeBackRay, camBackDir);

    float ray2wallDist;//m_eyeRay 2(to) 벽까지의 거리
    vector<D3DXVECTOR3> wall = g_pCameraManager->GetWall(); //벽의 정보를 갖고 있는 vector, 지금은 call by value 로 받고 있지만, 나중에는 reference로 받아서 성능을 빨리 하자
    
    m_distance = TP_DISTANCE; //Ray가 벽을 걸리지 않을 경우 distance 초기화
    for (size_t i = 0u; i < wall.size(); i+=3)
    {
        //ray가 벽에 걸리게 된다면
        if (m_pCamBackCheckingRay->CalcIntersectTri(&wall[i], &ray2wallDist))
        {
            //이범위 안에 들어 올때만 distance값을 변경
            if (4.0f <= ray2wallDist && ray2wallDist <= 11)
            {
                m_distance = ray2wallDist - 2.0f;
                break; //for 문을 더 돌아서 낭비하지 않기
            }
        }
    }

}



//--------------------------------------------


CameraTPToFP::CameraTPToFP()
    : ThirdPersonCamera()
    , m_vel(0.0f)
{
    m_cameraState = CameraState::TP2FP;
}

CameraTPToFP::~CameraTPToFP()
{
}

void CameraTPToFP::Init()
{
    m_distance = TP_DISTANCE;
    m_vel = 0.0f;
    //m_fovY = D3DX_PI * (80.0f / 180.0f);    //80 Degrees TP sight
    ThirdPersonCamera::Init();
}

void CameraTPToFP::Update()
{
    const auto dt = g_pTimeManager->GetDeltaTime();
    m_vel += dt * 5.0f;
    m_distance -= m_vel * dt;
    //m_fovY-= m_vel * dt*0.3f;
    //D3DXMatrixPerspectiveFovLH(&m_matProj, m_fovY, m_aspect, 1, 1000);
    //g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
    if(m_distance <= TP_DISTANCE-1.0f)
        g_pCameraManager->SetCurrentCamera(CameraState::FIRSTPERSON);
    ThirdPersonCamera::Update();
}
CameraFPToTP::CameraFPToTP()
    : ThirdPersonCamera()
    , m_vel(0.0f)
{
    m_cameraState = CameraState::FP2TP;
}

CameraFPToTP::~CameraFPToTP()
{
}

void CameraFPToTP::Init()
{
    m_distance = TP_DISTANCE-1.0f;
    m_vel = 4.0f;
    //m_fovY = ?;    //Unknown sight
    ThirdPersonCamera::Init();
}

void CameraFPToTP::Update()
{
    const auto dt = g_pTimeManager->GetDeltaTime();
    m_vel -= dt * 5.0f;
    m_distance += m_vel * dt;
    //m_fovY += m_vel * dt*0.3f;
    //D3DXMatrixPerspectiveFovLH(&m_matProj, m_fovY, m_aspect, 1, 1000);
    //g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
    if (m_distance>= TP_DISTANCE-0.01f)
        g_pCameraManager->SetCurrentCamera(CameraState::THIRDPERSON);
    ThirdPersonCamera::Update();
}

//--------------------------------------------

CameraKyunChak::CameraKyunChak()
    :ThirdPersonCamera()
    ,m_vel(0.0f)
{
    m_cameraState = CameraState::KYUNCHAK;
}

CameraKyunChak::~CameraKyunChak()
{
}

void CameraKyunChak::Init()
{
    m_distance = TP_DISTANCE;
    m_basePosY = TP_BASEPOSY;
    ThirdPersonCamera::Init();
}

void CameraKyunChak::Update()
{
    const auto dt = g_pTimeManager->GetDeltaTime();
    const float factor = 5.0f;
    bool bR_buttonStay = g_pKeyManager->IsStayKeyDown(VK_RBUTTON);
    bool bR_buttonUp = g_pKeyManager->IsOnceKeyUp(VK_RBUTTON);
    
    if (bR_buttonStay)//R_button이 눌릴때 까지만
    {
        if (m_distance >= TP_DISTANCE - factor)//견착모드
        {
            m_vel += dt * factor;
            m_distance -= m_vel * dt;
            m_basePosY -= m_vel * dt * 0.5f;
        }
    }
    else//R_button이 때어졌을때
    {
        //bR_buttonUp true, distance가 약간 작을때/ 즉 (우측 클릭을 잠깐 눌렸을때)(조준으로 넘어감)
        if (bR_buttonUp&&m_distance >= TP_DISTANCE-1.0f)
        {
            //!!! 앞으로 이곳에서 캐릭터가 들고 있는 아이템에 따라(2배율,4배율 no 배율 등) 바꾸어 주는 코드를 만들어야 한다.
            g_pCameraManager->SetCurrentCamera(CameraState::FIRSTPERSON);
            //g_pCameraManager->SetCurrentCamera(CameraState::SCOPE2X);
            //g_pCameraManager->SetCurrentCamera(CameraState::SCOPE4X);
        }
        else//아닌경우 계속 줄여주다가 끝에 다달게 되면 TP로 바꿈
        {
            if (m_distance <= TP_DISTANCE - 0.15f)
            {
                m_vel -= dt * factor;
                m_distance += m_vel * dt;
                m_basePosY += m_vel * dt * 0.5f;
            }
            else
            {
                g_pCameraManager->SetCurrentCamera(CameraState::THIRDPERSON);
            }
        }

    }

    ThirdPersonCamera::Update();
}

//Debug->AddText(dt);
//Debug->EndLine();
//m_currTime += dt;
//D3DXVec2Lerp(&m_accelarate, &D3DXVECTOR2(1.0f, 0.0f), &D3DXVECTOR2(0.0f, 0.0f), m_currTime / m_totalTime);
//if (m_accelarate.x <= 0.0f)
//    g_pCameraManager->SetCurrentCamera(CameraState::THIRDPERSON);
//    
//const float factor = 0.1f;
//m_vel += m_accelarate.x * factor;
//m_distance += m_vel * dt;