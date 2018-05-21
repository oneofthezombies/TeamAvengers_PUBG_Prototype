#include "stdafx.h"
#include "SceneShotting.h"
#include "Ground.h"

SceneShotting::SceneShotting()
	: m_pGround(nullptr)
	, m_pTeapotMesh(nullptr)
	, m_pBulletMesh(nullptr)
{
}


SceneShotting::~SceneShotting()
{
	SAFE_RELEASE(m_pGround);
	SAFE_RELEASE(m_pTeapotMesh);
	SAFE_RELEASE(m_pBulletMesh);
}

void SceneShotting::Init()
{
	//바닥
	m_pGround = new Ground(6, 20, 2.f); 
	m_pGround->Init();
	AddSimpleDisplayObj(m_pGround);

	//x, y, z 기준선
	D3DCOLOR c;
	float halfLength = 15.f;
	c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(-halfLength, 0.0f, 0.0f), c));
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(halfLength, 0.0f, 0.0f), c));
	c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, -halfLength, 0.0f), c));
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, halfLength, 0.0f), c));
	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, -halfLength), c));
	m_vecBaseline.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, halfLength), c));

	//플레이어 매쉬
	D3DXCreateTeapot(g_pDevice, &m_pTeapotMesh, NULL);
	
	//총알 매쉬
	D3DXCreateCylinder(g_pDevice, 2.f, 2.f, 10.f, 15, 10, &m_pBulletMesh, NULL);

	//플레이어 설정
	m_player.life = 10;
	m_player.scale = 0.7f;
	m_player.rotY = -D3DXToRadian(90);
	m_player.pos = D3DXVECTOR3(0.f, 2.f, -9 * 2.f);
	m_player.velocity = 5.f; //초단위
	m_player.bulletFireTime = 0.4f;
	m_player.oldBulletFireTime = GetTickCount();

	D3DXMatrixScaling(&m_player.matScale, m_player.scale, m_player.scale, m_player.scale);
	D3DXMatrixTranslation(&m_player.matTranslation, m_player.pos.x, m_player.pos.y, m_player.pos.z);
	D3DXMatrixRotationY(&m_player.matRotY, m_player.rotY);

	//총알
	m_bulletProperty.bulletVelocity = 10.f; //초단위
	m_bulletProperty.scale = 0.08f;
	D3DXMatrixScaling(&m_bulletProperty.matScale, m_bulletProperty.scale, m_bulletProperty.scale, m_bulletProperty.scale);
}

void SceneShotting::Update()
{
	OnUpdateIScene();

	float deltaTime = g_pTimeManager->GetDeltaTime(); //프레임당 경과시간, 초단위
	DWORD currentTime = GetTickCount();

	//움직임
	//플레이어의 이동은 프레임당 경과시간을 기준, (이동거리 =  속력 * 경과시간)이 된다.
	if (g_pKeyManager->IsStayKeyDown('A'))
	{
		if (m_player.pos.x - (deltaTime * m_player.velocity) >= -5.f)
			m_player.pos.x -= deltaTime * m_player.velocity;
	}
	if (g_pKeyManager->IsStayKeyDown('D'))
	{
		if (m_player.pos.x + (deltaTime  * m_player.velocity) <= 5.f)
			m_player.pos.x += deltaTime * m_player.velocity;
	}
	if (g_pKeyManager->IsStayKeyDown('W'))
	{
		if (m_player.pos.z + (deltaTime * m_player.velocity) <= 20.f)
			m_player.pos.z += deltaTime * m_player.velocity;
	}
	if (g_pKeyManager->IsStayKeyDown('S'))
	{
		if (m_player.pos.z - (deltaTime * m_player.velocity) >= -20.f)
			m_player.pos.z -= deltaTime * m_player.velocity;
	}
	
	//총알 발사
	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
	{
		//총알 발사는 지정된 발사 시간 간격으로, 이전에 발사한 시간과 현재 시간을 비교하여 미사일 발사의 여부를 결정한다
		//미사일 발사는 플레이어가 누르는 키에 따라 결정된다
		//oldBulletFireTime : 이전 시각을 저장하기 위함
		//bulletFireTime    : 미사일 발사 간격 설정
		if (currentTime - m_player.oldBulletFireTime >= m_player.bulletFireTime)
		{
			m_player.oldBulletFireTime = currentTime;

			for (int i = 0; i < 10; ++i)
			{
				if (m_bullet[i].life <= 0)
				{
					m_bullet[i].life = 1;
					m_bullet[i].pos = m_player.pos;
					std::cout << m_player.pos.x << ", " << m_player.pos.y << ", " << m_player.pos.z << std::endl;
					m_bullet[i].pos.z += 1.f; //플레이어보다 약간 앞쪽에서 발사
					break;
				}
			}
		}
	}

	//총알 이동
	for (int i = 0; i < 10; ++i)
	{
		if (m_bullet[i].life > 0)
		{
			m_bullet[i].pos.z += deltaTime * m_bulletProperty.bulletVelocity;
			if (m_bullet[i].pos.z >= 20.f) //경계 영역 충돌
				m_bullet[i].life = 0;
			else
				D3DXMatrixTranslation(&m_bullet[i].matTranslation, m_bullet[i].pos.x, m_bullet[i].pos.y, m_bullet[i].pos.z);
		}
	}

	D3DXMatrixTranslation(&m_player.matTranslation, m_player.pos.x, m_player.pos.y, m_player.pos.z);
	m_player.matWorld = m_player.matScale * m_player.matRotY * m_player.matTranslation;
}

void SceneShotting::Render()
{
	OnRenderIScene();


	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//기준선
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecBaseline.size() / 2, &m_vecBaseline[0], sizeof(VERTEX_PC));


	//총알
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	for (int i = 0; i < 10; ++i)
	{
		if (m_bullet[i].life > 0)
		{
			matWorld = m_bulletProperty.matScale * m_bullet[i].matTranslation;
			g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
			m_pBulletMesh->DrawSubset(0);
		}
	}

	//플레이어
	g_pDevice->SetTransform(D3DTS_WORLD, &m_player.matWorld);
	m_pTeapotMesh->DrawSubset(0);
}

void SceneShotting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
