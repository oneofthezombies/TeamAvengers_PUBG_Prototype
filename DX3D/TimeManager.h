#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
	SINGLETON(TimeManager)
private:
    system_clock::time_point prevTime;
    float deltaTime;
	float	sumTime;
	int		frameCnt;
	int		fps;

public:
	void	Update();
    float	GetDeltaTime() { return deltaTime; }
	int		GetFPS() { return fps; }
};

