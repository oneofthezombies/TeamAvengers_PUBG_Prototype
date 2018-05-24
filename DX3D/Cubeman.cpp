#include "stdafx.h"
#include "Cubeman.h"
#include "CubemanParts.h"
#include "IScene.h"
#include "Bullet.h"
#include "UIGameOver.h"
#include "Collider.h"

Cubeman::Cubeman()
    : IDisplayObject()
    , m_pBoxCollider(nullptr)
    , m_pCollisionListner(nullptr)
{
	m_pRootParts = NULL;

	m_isMoving = false;
	m_moveSpeed = 0.05f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;

	m_maxStepHeight = 2.0f;
}


Cubeman::~Cubeman()
{
}

void Cubeman::Init()
{
	//g_pCamera->SetTarget(&m_pos);
	//g_pKeyboardManager->SetMovingTarget(&m_deltaPos,
	//	&m_deltaRot, &m_isJumping);

	CreateAllParts();

    m_pCollisionListner = SetComponent<CubemanCollisionListner>();
    m_pBoxCollider = SetComponent<BoxCollider>();
    m_pBoxCollider->SetListner(*m_pCollisionListner);
    m_pBoxCollider->Init(D3DXVECTOR3(-2.0f, -3.0f, -0.7f), D3DXVECTOR3(2.0f, 3.0f, 0.7f));
    m_pBoxCollider->Move(D3DXVECTOR3(0.0f, 3.0f, 20.0f));
    m_pBoxCollider->SetTag(CollisionTag::kEnemy);

    m_rot.y += D3DX_PI;
}

void Cubeman::Update()
{
    const float prevZ = m_pos.z;
    m_deltaPos.z = 1.0f;

	UpdatePosition();
    const float currZ = m_pos.z;
	//if (GetAsyncKeyState('1') & 0x0001)
	//{
	//	m_isTurnedOnLight = !m_isTurnedOnLight;
	//}

	//if (m_isTurnedOnLight == true)
	//{
	//	D3DXVECTOR3 pos = m_pos;
	//	D3DXVECTOR3 dir = m_forward;
	//	D3DXCOLOR c = BLUE;
	//	D3DLIGHT9 light = DXUtil::InitSpot(&dir, &pos, &c);
	//	light.Phi = D3DX_PI / 4;
	//	//D3DLIGHT9 light = DXUtil::InitPoint(&pos, &c);
	//	g_pDevice->SetLight(10, &light);
	//}
	//g_pDevice->LightEnable(10, m_isTurnedOnLight);

	m_pRootParts->SetMovingState(m_isMoving);
	m_pRootParts->Update();

    D3DXMATRIXA16 m;
    D3DXMatrixTranslation(&m, 0.0f, 0.0f, currZ - prevZ);
    m_pBoxCollider->Update(m);
}

void Cubeman::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pRootParts->Render();
}

void Cubeman::UpdatePosition()
{
	m_rot += m_deltaRot * m_rotationSpeed;

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXVec3TransformNormal(&m_forward, 
		&D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;
	float basePosY = 0;
	bool	isIntersected = true;
	float	height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		targetPos = m_pos + m_forward * m_deltaPos.z
			* m_moveSpeed * m_currMoveSpeedRate ;


		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		targetPos = m_pos + m_forward * m_deltaPos.z
			* m_moveSpeed * m_currMoveSpeedRate;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}

		//m_pos = targetPos;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matRotY * matT;

	if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON ||
		D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
		m_isMoving = true;
	else
		m_isMoving = false;
}

void Cubeman::CreateAllParts()
{
	CubemanParts* pParts;
	//¸öÅë
	m_pRootParts = new CubemanParts();
	CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody);
	//¸Ó¸®
	pParts = new CubemanParts();
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
		D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead);
	//¿ÞÆÈ
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm);
	//¿À¸¥ÆÈ
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm);
	//¿Þ´Ù¸®
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg);
	//¿À¸¥´Ù¸®
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg);

}

void Cubeman::CreateParts(CubemanParts *& pParts,
	IDisplayObject * pParent, D3DXVECTOR3 pos, 
	D3DXVECTOR3 scale, D3DXVECTOR3 trans,
	vector<vector<int>> &vecUV)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	mat = matS * matT;
	pParts->Init(&mat, vecUV);
	pParts->SetPosition(pos);
	pParent->AddChild(*pParts);
}

CubemanCollisionListner::CubemanCollisionListner(BaseObject& owner)
    : ICollisionListner(owner)
{
}

void CubemanCollisionListner::OnCollisionEnter(const ColliderBase& other)
{
    auto a = static_cast<IDisplayObject*>(GetOwner());
    g_pCurrentScene->Destroy(a, 1.0f);
    auto b = static_cast<IDisplayObject*>(other.GetOwner());
    g_pCurrentScene->Destroy(b, 1.0f);

    UIGameOver* uigo = new UIGameOver;
    uigo->Init();
    g_pUIManager->RegisterUIObject(*uigo);
}

void CubemanCollisionListner::OnCollisionExit(const ColliderBase& other)
{
}

void CubemanCollisionListner::OnCollisionStay(const ColliderBase& other)
{
}
