#pragma once
#include "IDisplayObject.h"

class IUnitObject : public IDisplayObject
{
protected:
	D3DXVECTOR3      m_deltaPos;
	D3DXVECTOR3      m_deltaRot;
	D3DXVECTOR3      m_forward;

	KEYBOARD_STATE   m_keyState;

	bool          m_isMoving;
	float         m_moveSpeed;
	float         m_currMoveSpeedRate;
	float         m_rotationSpeed;

	bool		  m_isJumping;
	float         m_jumpPower;
	float         m_gravity;
	float         m_currGravity;

	float         m_maxStepHeight;
	float         m_baseRotY;

	D3DXVECTOR3	  m_destPos;//지금 내가 향하는 노드
	D3DXVECTOR3   m_finalDestPos;//결국 도착하게 되는 노드, 현재 노드들을 하나하나씩 따라서 도착
	vector<int>	  m_vecAStarIndex;

	IUnitObject();

public:

	virtual ~IUnitObject();

	void SetDestination(const D3DXVECTOR3 &pos);
	void UpdateKeyboardState();
	void UpdatePositionToDestination();

	void UpdateTargetPosition(OUT D3DXVECTOR3 &targetPos);
	void ApplyTargetPosition(D3DXVECTOR3 &targetPos);

	void UpdatePosition();
};