#include "stdafx.h"
#include "IScene.h"

void IScene::Destroy(IDisplayObject* p)
{
	for (auto& kv : m_deqToDeleteIDisplayObjects)
		if (kv.second == p) break;

	m_deqToDeleteIDisplayObjects.emplace_back(std::make_pair(0.0f, p));
}

void IScene::UpdateToDeleteIDisplayObjects()
{
	const float dt = g_pTimeManager->GetDeltaTime();
	for (auto it = m_deqToDeleteIDisplayObjects.begin(); it != m_deqToDeleteIDisplayObjects.end();)
	{
		it->first -= dt;
		if (it->first > 0.0f)
		{
			++it;
		}
		else
		{
			RemoveSimpleDisplayObj(it->second);
			SAFE_RELEASE(it->second);
			it = m_deqToDeleteIDisplayObjects.erase(it);
		}
	}
}
