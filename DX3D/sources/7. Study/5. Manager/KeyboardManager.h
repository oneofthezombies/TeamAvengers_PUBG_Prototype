#pragma once

#define g_pKeyboardManager KeyboardManager::GetInstance()

class KeyboardManager
{
	SINGLETON(KeyboardManager);
private:
	D3DXVECTOR3 * m_pTargetPos;
	D3DXVECTOR3 *	m_pTargetRot;
	bool*			m_pTargetIsJumping;
	KEYBOARD_STATE* m_pKeyState;

public:
	void Update();
	void UpdateMoving();
	void SetMovingTarget(D3DXVECTOR3* pPos, D3DXVECTOR3* pRot, bool* pIsJumping);
	
	void SetMovingTarget(KEYBOARD_STATE* pKeyState)
	{
		m_pKeyState = pKeyState;
	}
};

