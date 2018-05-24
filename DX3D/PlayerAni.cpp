#include "stdafx.h"
#include "PlayerAni.h"
#include "PlayerParts.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Collider.h"

enum enumParts
{
    head,
    left,
    right,
    leftleg,
    rightleg
};

PlayerAni::PlayerAni()
    : m_pPistol(nullptr)
	, m_pCollisionListner(nullptr)
	, m_pBoxCollider(nullptr)
{
    m_pRootParts = NULL;

    m_isMoving = false;
    m_moveSpeed = 0.2f;
    m_currMoveSpeedRate = 1.0f;
    m_rotationSpeed = 0.1f;

    m_isJumping = false;
    m_jumpPower = 1.0f;
    m_gravity = 0.05f;
    m_currGravity = 0.0f;

    m_maxStepHeight = 2.0f;

    m_isRunnig = false;
    m_isLive = true;
}


PlayerAni::~PlayerAni()
{
    //m_pRootParts->ReleaseAll();
	
	SAFE_DELETE(m_pBoxCollider);
	SAFE_DELETE(m_pCollisionListner);
}

void PlayerAni::Init()
{
	m_pos = D3DXVECTOR3(0.f, 0.f, -20.f); //시작 위치 박기

	g_pObjMgr->AddToTagList(TAG_PLAYER, this);

    //D3DXMATRIXA16 m;
    //D3DXMatrixRotationYawPitchRoll(&m, m_rot.y, m_rot.x, m_rot.z);
    //D3DXVec3TransformNormal(&m_dir, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &m);
    //D3DXVec3Normalize(&m_dir, &m_dir);

    g_pCameraManager->SetTarget(m_pos, m_rot);
    CreateAllParts();

	/* collider init */
	m_pCollisionListner = new PlayerAniCollisionListner(*this);
	
	m_pBoxCollider = new BoxCollider(*this);
	m_pBoxCollider->SetListner(*m_pCollisionListner);
	m_pBoxCollider->Init(D3DXVECTOR3(-2.0f, -3.0f, -0.7f), D3DXVECTOR3(2.0f, 3.0f, 0.7f));
	D3DXMATRIXA16 m;
	D3DXMatrixTranslation(&m, 0.0f, 3.0f, 0.0f);
	m_pBoxCollider->Update(m);
	/* end collider init */
}

void PlayerAni::Update()
{
	KeyMove();    //이동
	KeyMount();   //장착
	KeyUnmount(); //장착해제
	KeyLoad();    //총 장전
	KeyFire();    //총 쏘기


	//뛰고 걷기
	RunAndWalk();

    //const float dt = g_pTimeManager->GetDeltaTime();
    //POINT currPoint;
    //POINT m_ptPrevMouse;
    //m_ptPrevMouse = g_pKeyManager->GetPreviousMousePos();
    //currPoint = g_pKeyManager->GetCurrentMousePos();
    //POINT diff;
    //diff.x = currPoint.x - m_ptPrevMouse.x;
    //diff.y = currPoint.y - m_ptPrevMouse.y;
    //const float factorX = 0.1f;
    //const float factorY = 0.1f;
    //m_rot.x += diff.y * factorX * dt;
    //m_rot.y += diff.x * factorY * dt;

    if(g_pKeyManager->IsOnceKeyDown(VK_SPACE))
    {
        m_isJumping = true;
    }

	//죽는 애니메이션 테스트용
    if (g_pKeyManager->IsOnceKeyDown('G'))
    {
        DiedAni();
    }
    
	D3DXMATRIXA16 prevM = m_matWorld;
    if (m_isLive)
    {
        UpdatePosition();
    }
	D3DXMATRIXA16 currM = m_matWorld;
	D3DXMatrixInverse(&prevM, nullptr, &prevM);

    D3DXMATRIXA16 m;
    D3DXMatrixRotationYawPitchRoll(&m, m_rot.y, m_rot.x, m_rot.z);
    D3DXVec3TransformNormal(&m_dir, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &m);
    D3DXVec3Normalize(&m_dir, &m_dir);

    m_pRootParts->SetMovingState(m_isMoving);
    m_pRootParts->Update();

	/* 디버그 */
	//인벤토리 디버그용
	ShowInventoryForDebug();

	//총알 개수 디버그용
	if (m_pPistol)
		m_pPistol->ShowBulletNumForDebug();

	/* TM = prevM^(-1) * currM */
	m_pBoxCollider->Update(prevM * currM);
}

void PlayerAni::Render()
{
    g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
    m_pRootParts->Render();
}

void PlayerAni::UpdatePosition()
{
    m_rot += m_deltaRot * m_rotationSpeed;
    D3DXMATRIXA16 matRotY;

    if (m_isLive)
    {
        D3DXMatrixRotationY(&matRotY, m_rot.y);
        D3DXVec3TransformNormal(&m_forward,
            &D3DXVECTOR3(0, 0, 1), &matRotY);
    }
    else
    {
        D3DXMatrixRotationX(&matRotY, m_rot.x);
        D3DXVec3TransformNormal(&m_forward,
            &D3DXVECTOR3(0, 0, 1), &matRotY);
    }


    D3DXVECTOR3 targetPos;
    float basePosY = 0;
    bool	isIntersected = true;
    float	height = 0;

    if (m_isJumping == true)
    {
        m_currMoveSpeedRate = 0.7f;
        targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;

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
				/* nothing */
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

void PlayerAni::CreateAllParts()
{
    PlayerParts* pParts;
    //몸통
    m_pRootParts = new PlayerParts();
    CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),
        D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody, tEmpty);
    //머리
    pParts = new PlayerParts();
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
        D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead, tEmpty);
    //왼팔
    pParts = new PlayerParts(0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm, tEmpty);
    //오른팔
    pParts = new PlayerParts(-0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm, tEmpty);
    //왼다리
    pParts = new PlayerParts(-0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg, tEmpty);
    //오른다리
    pParts = new PlayerParts(0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg, tEmpty);
}

void PlayerAni::CreateParts(PlayerParts *& pParts, IDisplayObject * pParent, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans, vector<vector<int>>& vecUV, PartTag tag)
{
    D3DXMATRIXA16 matS, matT, mat;
    D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
    D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
    mat = matS * matT;
    pParts->Init(&mat, vecUV);
    pParts->SetPosition(&pos);
    pParts->SetPartTag(tag);
    pParent->AddChild(*pParts);

}

void PlayerAni::DrawGunInOut()
{
    PartTag tag = GetChild(right)->GetPartTag();
    float tem_rotX = GetChild(left)->GetRotXspeed();

    if (tag != tEmpty)
    {
        GetChild(right)->SetPartTag(tEmpty);
        GetChild(right)->SetRotXspeed(-1 * tem_rotX);
        GetChild(right)->SyncMotion();
    }
    else
    {
        GetChild(right)->SetPartTag(tGun);
    }
}

void PlayerAni::RunAndWalk()
{
    if (g_pKeyManager->IsStayKeyDown(VK_LSHIFT))
    {
        if (m_isRunnig == false)
        {
            m_moveSpeed = 0.35;
            for (int i = 1; i < m_pRootParts->GetChildVec().size(); i++)
            {
                GetChild(i)->SetRotXspeed(GetChild(i)->GetRotXspeed() * 1.5f);
            }
            m_isRunnig = true;
        }
    }
    else
    {
        if (m_isRunnig == true)
        {
            m_moveSpeed = 0.2f;
            for (int i = 1; i < m_pRootParts->GetChildVec().size(); i++)
            {
                GetChild(i)->SetRotXspeed(GetChild(i)->GetRotXspeed()/ 1.5f);
            }
            m_isRunnig = false;
        }
    }
}

void PlayerAni::DiedAni()
{
    if (m_isLive == true)
    {
        m_isLive = false;
        m_rot.x = D3DX_PI / 2.1f;
        UpdatePosition();
        m_isMoving = false;
    }
}

/* 우리 추가 */
void PlayerAni::PutItemInInventory(Item* item)
{
	item->SetItemState(ITEM_STATE::InInventory);
	m_mapInventory[item->GetItemTag()].push_back(item);
}
void PlayerAni::ShowInventoryForDebug()
{
	Debug->AddText("<Inventory>");
	Debug->EndLine();
	Debug->AddText("the number of Items: ");
	Debug->AddText(GetInventorySize());
	Debug->EndLine();

	for (auto item : m_mapInventory)
	{
		auto itemTag = item.first;
		switch (itemTag)
		{
		case ITEM_TAG::Pistol:
			Debug->AddText("- Pistol: ");
			Debug->AddText(item.second.size());
			Debug->EndLine();

			for (auto i : item.second)
			{
				switch (i->GetItemState())
				{
				case ITEM_STATE::Dropped:
					Debug->AddText("Dropped");
					break;
				case ITEM_STATE::InInventory:
					Debug->AddText("InInventory");
					break;
				case ITEM_STATE::Mounting:
					Debug->AddText("Mounting");
					break;
				} //swtich ItemState
				Debug->EndLine();
			} // for item.second()

			break;
		case ITEM_TAG::Bullet:
			Debug->AddText("- Bullet: ");
			Debug->AddText(item.second.size());
			Debug->EndLine();

			for (auto i : item.second)
			{
				switch (i->GetItemState())
				{
				case ITEM_STATE::Dropped:
					Debug->AddText("Dropped");
					break;
				case ITEM_STATE::InInventory:
					Debug->AddText("InInventory");
					break;
				case ITEM_STATE::Mounting:
					Debug->AddText("Mounting");
					break;
				} //swtich ItemState
				Debug->EndLine();
			} // for item.second()
			break;
		} //switch itemTag
	} //for m_mapInventory
}


/* 키 입력 관련 함수로 분리 */
void PlayerAni::KeyMove()
{
	//float deltaTime = g_pTimeManager->GetDeltaTime();
	//float distance = deltaTime * m_velocity;

	/* 이동 ASDW */ // 맵 구역 안에 있을 때만 움직인다 
	if (g_pKeyManager->IsStayKeyDown('A')) //왼쪽
	{
		//if (m_pos.x - distance >= -5.f)
		//	m_pos.x -= distance;
		m_deltaRot = D3DXVECTOR3(0, -1, 0);
	}
	else if (g_pKeyManager->IsStayKeyDown('D')) //오른쪽
	{
		//if (m_pos.x + distance <= 5.f)
		//	m_pos.x += distance;
		m_deltaRot = D3DXVECTOR3(0,  1, 0);
	}
	else
	{
		m_deltaRot = D3DXVECTOR3(0, 0, 0);
	}

	if (g_pKeyManager->IsStayKeyDown('W')) //위쪽
	{
		//if (m_pos.z + distance <= 20.f)
		//	m_pos.z += distance;
		m_deltaPos.z = 1;
	}
	else if (g_pKeyManager->IsStayKeyDown('S')) //아래쪽
	{
		//if (m_pos.z - distance >= -20.f)
		//	m_pos.z -= distance;
		m_deltaPos.z = -1;
	}
	else
	{
		m_deltaPos.z = 0;
	}

	/* 총 장착시 총 위치 업데이트 */
	if (m_pPistol)
	{
		m_pPistol->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 1.f, m_pos.z + 2.f)); //플레이어보다 살짝 위, 살짝 앞
	}
}

void PlayerAni::KeyMount()
{
	/* 무기 장착 */
	if (g_pKeyManager->IsOnceKeyDown('1'))
	{
		if (m_pPistol == nullptr) //아무것도 장착되어있지 않을 때
		{
			for (auto item : m_mapInventory) //인벤토리에서 총 찾아 가장 앞에 있는 총 겟또
			{
				auto itemTag = item.first;
				if (itemTag == ITEM_TAG::Pistol)
				{
					DrawGunInOut();
					m_pPistol = static_cast<Pistol*>(item.second.front());
					m_pPistol->SetItemState(ITEM_STATE::Mounting); //장착중
					std::cout << "장착 완료" << std::endl;
					break; //총한개만 찾지롱
				}
			}
		}
	}
}

void PlayerAni::KeyUnmount()
{
	/* 무기 장착 해제 */
	if (g_pKeyManager->IsOnceKeyDown('X'))
	{
		if (m_pPistol)
		{
			DrawGunInOut();
			m_pPistol->SetItemState(ITEM_STATE::InInventory); //장착해제중
			m_pPistol = nullptr;
			std::cout << "장착 해제" << std::endl;
		}
	}

}

void PlayerAni::KeyLoad()
{
	/* 총알 장전 */
	if (g_pKeyManager->IsOnceKeyDown('R'))
	{
		if (m_pPistol) //장착하고 있는 총이 있으면
		{
			//총알 찾기
			for (auto& item : m_mapInventory)
			{
				if (item.first == ITEM_TAG::Bullet)
				{
					int need = m_pPistol->GetNeedBullet(); //장전에 필요한 총알 수
					auto& bullets = item.second;
					for (int i = 0; i < need; ++i)
					{
						if (bullets.empty() == false)
						{
							auto bullet = bullets.back();
							bullet->SetItemState(ITEM_STATE::Mounting);
							m_pPistol->Load(static_cast<Bullet*>(bullet));
							bullets.pop_back();
							std::cout << "장전완료" << std::endl;
						}
					}
				}//if ITEM_TAG::Bullet
			}//for m_mapInventory
		}//if m_pPistol
		else //m_pPistpol == nullptr
		{
			std::cout << "총을 장착하고 장전해줘~!" << std::endl;
		}
	}
}

void PlayerAni::KeyFire()
{
	/* 총쏘기 RETRUN */ //TODO: 마우스 왼쪽 버튼으로 바꿔야함!!
	if (g_pKeyManager->IsOnceKeyDown(VK_RETURN))
	{
		if (m_pPistol) //총이 장착되어있을 때
		{
			m_pPistol->Fire();
			if (m_pPistol->GetBulletNum() > 0)
				std::cout << "빵야빵야~!" << std::endl;
			else
				std::cout << "총알이 없따 ㅠㅠㅠㅠ" << std::endl;
		}
		else
		{
			std::cout << "총을 장착해줘!" << std::endl;
		}
	}
}

PlayerAniCollisionListner::PlayerAniCollisionListner(BaseObject & owner)
	: ICollisionListner(owner)
{
}

void PlayerAniCollisionListner::OnCollisionEnter(const ColliderBase & other)
{
}

void PlayerAniCollisionListner::OnCollisionExit(const ColliderBase & other)
{
}

void PlayerAniCollisionListner::OnCollisionStay(const ColliderBase & other)
{
}
