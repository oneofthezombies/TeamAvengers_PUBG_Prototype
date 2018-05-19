#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
	prevTime = GetTickCount();
	sumTime = 0;
	frameCnt = 0;
}


TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	auto currentTime = GetTickCount();
	deltaTime = currentTime - prevTime;
	prevTime = currentTime;

	frameCnt++;
	sumTime += deltaTime;
	if (sumTime >= 200)
	{
		fps = frameCnt / sumTime * 1000.0f;
		frameCnt = 0;
		sumTime = 0;
	}

	Debug->AddText("FPS : ");
	Debug->AddText(fps);
	Debug->EndLine();

}
