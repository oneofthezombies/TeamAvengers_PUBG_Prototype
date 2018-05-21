#pragma once

#define g_pCameraManager CameraManager::GetInstance()
#define g_pCurrentCamera CameraManager::GetInstance()->GetCurrentMap()

class ICamera;

class CameraManager
{
    SINGLETON(CameraManager)

private:
    ICamera * m_pCurrentCamera;
    map<string, ICamera*> m_mapList;

public:
    //이렇게 까지 할 필요가 없을까? 단지 First와 Third만 사용할 것이기 때문에?
    //그럼 enum은 어디에다가 넣어야 하는가?
    void AddCamera(string cameraName, ICamera* pCamera)
    {
        if (m_mapList.count(cameraName) == 1)
            return;
        m_mapList[cameraName] = pCamera;
    }
    void SetCurrentCamera(string cameraName)
    { m_pCurrentCamera = m_mapList[cameraName]; }
    ICamera* GetCurrentCamera() { return m_pCurrentCamera; }
};

