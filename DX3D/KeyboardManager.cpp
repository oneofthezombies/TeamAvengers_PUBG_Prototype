#include "stdafx.h"
#include "KeyboardManager.h"


KeyboardManager::KeyboardManager()
{
}


KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Update()
{
	UpdateMoving();
}

void KeyboardManager::UpdateMoving()
{
	//if (m_pTargetPos == NULL || m_pTargetRot == NULL)
	//	return;
	if (m_pKeyState == NULL)
		return;

	if (GetKeyState('A') & 0x8000)
	{
		//m_pTargetRot->y = -1;
		m_pKeyState->deltaRot.y = -1;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		//m_pTargetRot->y = 1;
		m_pKeyState->deltaRot.y = 1;
	}
	else
	{
		//m_pTargetRot->y = 0;
		m_pKeyState->deltaRot.y = 0;
	}

	if (GetKeyState('W') & 0x8000)
	{
		//m_pTargetPos->z = 1;
		m_pKeyState->deltaPos.z = 1;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		//m_pTargetPos->z = -1;
		m_pKeyState->deltaPos.z = -1;
	}
	else
	{
		//m_pTargetPos->z = 0;
		m_pKeyState->deltaPos.z = 0;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001) //VK_SPACE가 눌렸을 때 한번만 적용되며
		                                     //Async이므로 내 코드와 별개로 외부에서 비동기적으로 처리
		m_pKeyState->bJump = true;
	else
		m_pKeyState->bJump = false;

	//Debug->AddText("bJump :" );
	//Debug->AddText(m_pKeyState->bJump);
	//Debug->EndLine();
	//{
	//	if (*m_pTargetIsJumping == false) 
	//		*m_pTargetIsJumping = true;
	//}
}

void KeyboardManager::SetMovingTarget(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pRot,
	bool* pIsJumping)
{
	m_pTargetPos = pPos;
	m_pTargetRot = pRot;
	m_pTargetIsJumping = pIsJumping;
}
