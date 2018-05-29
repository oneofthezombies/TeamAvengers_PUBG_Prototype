#include "stdafx.h"
#include "PlayerAni.h"
#include "PlayerParts.h"
#include "Gun.h"
#include "Bullet.h"
#include "Collider.h"
#include "ItemPicker.h"
#include "UIInventory.h"
#include "UIInGame.h"
#include "UIGameOver.h"
#include "CubemanBarrack.h"
#include "Ray.h"

enum enumParts
{
    head,
    left,
    right,
    leftleg,
    rightleg
};

PlayerAni::PlayerAni()
    : m_fireMode(FIRE_MODE::Idle)
	, m_pGun(nullptr)
	, m_pBoxCollider(nullptr)
    , m_pCollisionListener(nullptr)
    , m_pItemPicker(nullptr)
    , m_pUIInventory(nullptr)
    , m_pPicked(nullptr)
    , m_vRotForAlt()
    , m_forward(0.0f, 0.0f, 1.0f)
    , m_isGameOver(false)
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
    SAFE_RELEASE(m_pItemPicker);
}

void PlayerAni::Init()
{
	//m_pos = D3DXVECTOR3(0.f, 0.f, -20.f);
    m_pos = D3DXVECTOR3(30.0f, 0.0f, 30.0f);

	g_pObjMgr->AddToTagList(TAG_PLAYER, this);

    g_pCameraManager->SetTarget(m_pos, m_rot);
    CreateAllParts();

	/* collider init */
    m_pCollisionListener = SetComponent<PlayerAniCollisionListener>();

    m_pBoxCollider = SetComponent<BoxCollider>();
    m_pBoxCollider->SetListener(*m_pCollisionListener);
	m_pBoxCollider->Init(D3DXVECTOR3(-2.0f, 0.0f, -0.7f), D3DXVECTOR3(2.0f, 6.0f, 0.7f));
    m_pBoxCollider->SetTag(CollisionTag::kPlayer);
    /* end collider init */

    ShowCursor(true);     

    UIInGame::Create(&m_pGun, &m_fireMode);
}

void PlayerAni::Update()
{   
    if (m_isGameOver)
    {
        if (IsShowingInventory())
        {
            SAFE_RELEASE(m_pItemPicker);
            g_pUIManager->Destroy(*m_pUIInventory);
            m_pUIInventory = nullptr;
        }

        return;
    }

    //이동 ASDW
    KeyMove();

    if (!IsShowingInventory())
    {
        UpdateRotation();
        UpdateDirection();

        //장착 1, 2
        if (g_pKeyManager->IsOnceKeyDown('1'))
            KeyChangeGun(GUN_TAG::Pistol);
        else if (g_pKeyManager->IsOnceKeyDown('2'))
            KeyChangeGun(GUN_TAG::Rifle);
        //장착해제 X
        if (g_pKeyManager->IsOnceKeyDown('X'))
            KeyOutHand();
        //총 장전 R
        if (g_pKeyManager->IsOnceKeyDown('R'))
            KeyLoad();
        //총 모드 변경(단발 <-> 연발) B
        if (g_pKeyManager->IsOnceKeyDown('B'))
            KeyChangeFireMode();
        //총 쏘기(단발) 마우스 왼쪽버튼
        if (m_fireMode == FIRE_MODE::SingleShot)
        {
            if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
                //KeyFire(m_dir); 
            {//JH
                m_camDir = FireDirection();
                KeyFire(m_camDir);
            }
                
        }
        //총 쏘기(연발)
        else if (m_fireMode == FIRE_MODE::Burst)
        {
            if (m_pGun)
            {
                if (m_pGun->GetCanChangeBurstMode())             //연발이 지원되는 총이라면
                {
                    if (g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
                        //KeyFire(m_dir);
                    {//JH
                        m_camDir = FireDirection();
                        KeyFire(m_camDir);
                    }
                }
                else //m_pGun->GetCanChangeBurstMode() == false //연발이 지원되지 않는 총이라면
                {
                    if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
                        //KeyFire(m_dir);
                    {//JH
                        m_camDir = FireDirection();
                        KeyFire(m_camDir);
                    }
                }
            }
        }

        //뛰고 걷기 LShift
        RunAndWalk(); 
    }

	//점프 Space
    if(g_pKeyManager->IsOnceKeyDown(VK_SPACE))
        m_isJumping = true;

	//죽는 애니메이션 테스트용 G
    if (g_pKeyManager->IsOnceKeyDown('G'))
        DiedAni();

    if (m_isLive)
        UpdatePosition();

    m_pRootParts->SetMovingState(m_isMoving);
    m_pRootParts->Update();

	m_pBoxCollider->Update(m_matWorld);

    // change position for Gun in hand
    UpdateGunInHandPosition();
    UpdateGunInEquipPosition();

	/* 디버그 */
    //발사모드 디버그용
    ShowFireModeForDebug();

	//인벤토리 디버그용
	ShowInventoryForDebug();

	//총알 개수 디버그용
	if (m_pGun)
		m_pGun->ShowBulletNumForDebug();

    ShowInventory(m_matWorld);

    if (g_pKeyManager->IsOnceKeyDown('8'))
    {
        Bullet* bullet = new Bullet(GUN_TAG::Pistol, 0.08f, 10.f);
        bullet->Init();
        bullet->SetPosition(m_pos);
        bullet->SetHeightOffset(0.5f);
        bullet->UpdatePositionYOnMap();
        g_pCurrentScene->AddSimpleDisplayObj(bullet);
        Pick(*bullet);
    }

    IDisplayObject* search = g_pObjMgr->FindObjectByTag(TAG_CUBEMAN_BARRACK);
    if (search)
    {
        CubemanBarrack* cb = static_cast<CubemanBarrack*>(search);
        if (cb->GetNumCubemans() == 0)
        {
            UIGameOver* uigo = new UIGameOver;
            uigo->Init(true, 1, 4);
            g_pUIManager->RegisterUIObject(*uigo);

            IDisplayObject* search = g_pObjMgr->FindObjectByTag(TAG_DISPLAYOBJECT::TAG_PLAYER);
            if (!search) return;

            PlayerAni* player = static_cast<PlayerAni*>(search);
            player->SetIsGameOver(true);
        }
    }
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
        D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

        D3DXMatrixRotationY(&matRotY, m_rot.y);
        D3DXVec3TransformNormal(&m_right, &D3DXVECTOR3(1, 0, 0), &matRotY);
    }
    else
    {
        D3DXMatrixRotationX(&matRotY, m_rot.x);
        D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);
    }

    D3DXVECTOR3 targetPos;
    float basePosY = 0;
    bool	isIntersected = true;
    float	height = 0;

    if (m_isJumping == true)
    {
        m_currMoveSpeedRate = 0.7f;
        targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate
            + m_right * m_deltaPos.x*m_moveSpeed *m_currMoveSpeedRate;

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
            * m_moveSpeed * m_currMoveSpeedRate
            + m_right * m_deltaPos.x*m_moveSpeed *m_currMoveSpeedRate;

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
    //m_pos.x += m_deltaPos.x * m_moveSpeed;
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

    // body
    m_pRootParts = new PlayerParts();
    CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),
        D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody, tEmpty);

    // head
    pParts = new PlayerParts();
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
        D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead, tEmpty);

    // left arm
    pParts = new PlayerParts(0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm, tEmpty);

    // right arm
    pParts = new PlayerParts(-0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm, tEmpty);

    // left leg
    pParts = new PlayerParts(-0.1f);
    CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
        D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg, tEmpty);

    // right leg
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
    pParts->SetPosition(pos);
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
        g_pSoundManager->Play(static_cast<int>(SOUND_TAG::DieFemale), SOUND_TAG::DieFemale);
        m_isLive = false;
        m_rot.x = D3DX_PI / 2.1f;
        UpdatePosition();
        m_isMoving = false;
        m_isGameOver = true;
    }
}

PlayerParts * PlayerAni::GetChild(int index)
{
    return static_cast<PlayerParts*>(m_pRootParts->GetChildVec()[index]);
}

size_t PlayerAni::GetInventorySize()
{
    return m_mapInventory.size();
}

size_t PlayerAni::GetGunsNum()
{
    return m_mapGuns.size();
}

void PlayerAni::PutItemInInventory(Item* item)
{
	item->SetItemState(ITEM_STATE::InInventory);
	m_mapInventory[item->GetItemTag()].push_back(item);
}

void PlayerAni::PutGunInEquip(Gun* gun)
{
	gun->SetItemState(ITEM_STATE::Equipped);
	m_mapGuns[gun->GetGunTag()] = gun;
    UpdateGunInEquipPosition();
}

void PlayerAni::KeyMove()
{
	if (g_pKeyManager->IsStayKeyDown('A'))
	{
        g_pSoundManager->RepeatPlay(static_cast<int>(SOUND_TAG::Footstep), SOUND_TAG::Footstep);
        m_deltaPos.x = -1;
	}
	else if (g_pKeyManager->IsStayKeyDown('D'))
	{
        g_pSoundManager->RepeatPlay(static_cast<int>(SOUND_TAG::Footstep), SOUND_TAG::Footstep);
        m_deltaPos.x = 1;
    }
	else
	{
        m_deltaPos.x = 0;
    }

	if (g_pKeyManager->IsStayKeyDown('W'))
	{
        g_pSoundManager->RepeatPlay(static_cast<int>(SOUND_TAG::Footstep), SOUND_TAG::Footstep);
		m_deltaPos.z = 1;
	}
	else if (g_pKeyManager->IsStayKeyDown('S'))
	{
        g_pSoundManager->RepeatPlay(static_cast<int>(SOUND_TAG::Footstep), SOUND_TAG::Footstep);
		m_deltaPos.z = -1;
	}
	else
	{
		m_deltaPos.z = 0;
	}
}

void PlayerAni::KeyInHand(GUN_TAG gunTag)
{
	/* 무기 장착 */
	for (auto gun : m_mapGuns)
	{
		if (gun.first == gunTag)
		{
            g_pSoundManager->Play(static_cast<int>(SOUND_TAG::InHand), SOUND_TAG::InHand);

			DrawGunInOut();
			m_pGun = static_cast<Gun*>(gun.second);
			m_pGun->SetItemState(ITEM_STATE::InHand); //장착중
            m_fireMode = FIRE_MODE::SingleShot;
			cout << m_pGun->GunTagToStrForDebug(gunTag) << " OK, Mount." << endl;
			break; //총한개만 찾지롱
		}
	}
}

void PlayerAni::KeyOutHand()
{
	/* 무기 장착 해제 */
	if (m_pGun)
	{
        g_pSoundManager->Play(static_cast<int>(SOUND_TAG::OutHand), SOUND_TAG::OutHand);
		DrawGunInOut();
		m_pGun->SetItemState(ITEM_STATE::Equipped); //장착해제중
		m_pGun = nullptr;
		cout << "Ok, Unmount." << endl;
	}
}

void PlayerAni::KeyLoad()
{
	/* 총알 장전 */
	if (m_pGun) //장착하고 있는 총이 있으면
	{
		//총알 찾기
		for (auto& item : m_mapInventory)
		{
			if (item.first == ITEM_TAG::Bullet)
			{
				int need = m_pGun->GetNeedBullet(); //장전에 필요한 총알 수
				auto& bullets = item.second;
				vector<Bullet*> vecSpecificBullets; //특정 총알 리스트를 만든다
				for (auto bullet : bullets)
				{
					auto pBullet = static_cast<Bullet*>(bullet);
					if (pBullet->GetBulletFor() == m_pGun->GetGunTag())
						vecSpecificBullets.emplace_back(pBullet);
				}

                if(vecSpecificBullets.empty() == false)
                    g_pSoundManager->Play(static_cast<int>(SOUND_TAG::Reload), SOUND_TAG::Reload);

				for (int i = 0; i < need; ++i)
				{
					if(vecSpecificBullets.empty() == false) //특정 총알 리스트에 대해 진행
					{
						auto pLastBullet = static_cast<Bullet*>(vecSpecificBullets.back());
						if(pLastBullet->IsBulletForThisGun(m_pGun->GetGunTag()))
						{
							pLastBullet->SetItemState(ITEM_STATE::InHand);
							m_pGun->Load(pLastBullet);
							for (auto it = bullets.begin(); it != bullets.end(); )
							{
								if (*it == static_cast<Item*>(vecSpecificBullets.back()))
									it = bullets.erase(it);
								else
									++it;
							}
							vecSpecificBullets.pop_back();
							cout << "Ok, Load." << endl;
						}
						else
						{
							cout << "This Bullet can't be used for this Gun." << endl;
						}
					}
				}//for need
			}//if ITEM_TAG::Bullet
		}//for m_mapInventory
	}//if m_pGun
	else //m_pPistpol == nullptr
	{
		cout << "Plz, Load after mounting gun." << endl;
	}
}

D3DXVECTOR3 PlayerAni::FireDirection()
{
    Ray camRay(g_pCameraManager->GetCurrentCameraEye(), g_pCameraManager->GetCurrentCameraDir());
    //camRay.CalcIntersectTri
    

    return D3DXVECTOR3(0, 0, 0);
}

void PlayerAni::KeyFire(const D3DXVECTOR3& dir)
{
    if (m_pGun) //총이 장착되어있을 때
    {
		if (m_pGun->GetBulletNum() > 0)

        {
            //Sound shot
            if(m_fireMode == FIRE_MODE::SingleShot)
                g_pSoundManager->Play(static_cast<int>(SOUND_TAG::OneShot), SOUND_TAG::OneShot);
            else if(m_fireMode == FIRE_MODE::Burst)
                g_pSoundManager->RepeatPlay(static_cast<int>(SOUND_TAG::Burst), SOUND_TAG::Burst);
			m_pGun->Fire(dir);
		}
        else
        {
            cout << "No Bullet!!" << endl;
        }
	}
	else
	{
		cout << "Plz, Mount Gun." << endl;
	}
}

void PlayerAni::KeyChangeGun(GUN_TAG gunTag)
{
	if (m_pGun == nullptr) //아무것도 장착되어있지 않을 때
	{
		KeyInHand(gunTag);
	}
	else if (m_pGun && m_pGun->GetGunTag() != gunTag) //장착이 되어있으면서, 이미 장착하고 있는 총이 아닐 때
	{
		//장착 해제 후 장착
		KeyOutHand(); 
		KeyInHand(gunTag);
	}
}

void PlayerAni::KeyChangeFireMode()
{
    if (m_pGun)
    {
        if (m_fireMode == FIRE_MODE::SingleShot)
        {
            if (m_pGun->GetCanChangeBurstMode())
                m_fireMode = FIRE_MODE::Burst;
        }
        else if (m_fireMode == FIRE_MODE::Burst)
            m_fireMode = FIRE_MODE::SingleShot;
    }
}

void PlayerAni::UpdateRotation()
{
    const float dt = g_pTimeManager->GetDeltaTime();

    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient(g_hWnd, &mouse);

    POINT diff;
    diff.x = mouse.x - 1280 / 2;
    diff.y = mouse.y - 720 / 2;
    const float factorX = 0.3f;
    const float factorY = 0.3f;

    if (g_pKeyManager->IsOnceKeyDown(VK_MENU))
    {
        m_vRotForAlt = m_rot;
    }

    if (g_pKeyManager->IsStayKeyDown(VK_MENU) &&
        g_pCurrentCamera->GetState() == CameraState::THIRDPERSON)
    {
        m_vRotForAlt.x += diff.y * factorX * dt;
        m_vRotForAlt.y += diff.x * factorY * dt;
        g_pCameraManager->SetTarget(m_pos, m_vRotForAlt);

    }
    else
    {
        m_rot.x += diff.y * factorX * dt;
        m_rot.y += diff.x * factorY * dt;
        g_pCameraManager->SetTarget(m_pos, m_rot);
    }

    POINT center;
    center.x = 1280 / 2;
    center.y = 720 / 2;
    ClientToScreen(g_hWnd, &center);
    SetCursorPos(center.x, center.y);
}

void PlayerAni::UpdateDirection()
{
    D3DXMATRIXA16 r;
    D3DXMatrixRotationYawPitchRoll(&r, m_rot.y, m_rot.x, m_rot.z);
    D3DXVec3TransformNormal(&m_dir, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r);
    D3DXVec3Normalize(&m_dir, &m_dir);
}

void PlayerAni::UpdateGunInHandPosition()
{
    /* 총 장착시 총 위치 업데이트 */
    if (m_pGun)
    {
        m_pGun->SetPosition(D3DXVECTOR3(
            m_pos.x + m_forward.x * 2.3f + m_right.x * 1.3f,
            m_pos.y + 4.f,
            m_pos.z + m_forward.z * 2.3f + m_right.z * 1.3f));

        m_pGun->SyncRot(m_rot.y);
    }
}

void PlayerAni::UpdateGunInEquipPosition()
{
    for (auto gun : m_mapGuns)
    {
        if (gun.second->GetItemState() == ITEM_STATE::Equipped)
        {
            switch (gun.second->GetGunTag())
            {
            case GUN_TAG::Pistol:
                gun.second->SetPosition(D3DXVECTOR3(
                    m_pos.x + m_forward.x * -1.3f + m_right.x * -0.3f,
                    m_pos.y + 3.f,
                    m_pos.z + m_forward.z * -1.3f + m_right.z * -0.3f));
                break;
            case GUN_TAG::Rifle:
                gun.second->SetPosition(D3DXVECTOR3(
                    m_pos.x + m_forward.x * -1.3f + m_right.x * 0.3f,
                    m_pos.y + 4.f,
                    m_pos.z + m_forward.z * -1.3f + m_right.z * 0.3f));
                break;
            }
            gun.second->SyncRot(m_rot.y + D3DXToRadian(90));
        }
    }
}

void PlayerAni::ShowInventory(const D3DXMATRIXA16& transform)
{
    if (g_pKeyManager->IsOnceKeyDown(VK_TAB))
    {
        if (m_pItemPicker)
        {
            SAFE_RELEASE(m_pItemPicker);
            g_pUIManager->Destroy(*m_pUIInventory);
            m_pUIInventory = nullptr;

            POINT center;
            center.x = 1280 / 2;
            center.y = 720 / 2;
            ClientToScreen(g_hWnd, &center);
            SetCursorPos(center.x, center.y);
        }
        else
        {
            m_pItemPicker = ItemPicker::Create(*this, m_pos, m_rot);
            m_pUIInventory = UIInventory::Create();
            m_pUIInventory->AttachToObject(*this);
        }
    }

    if (m_pItemPicker && m_pUIInventory)
    {
        vector<Item*> pickables;
        m_pItemPicker->Update(pickables, transform);
        m_pUIInventory->Update(m_pPicked, m_mapInventory, pickables, m_mapGuns);
    }
}

bool PlayerAni::IsShowingInventory()
{
    return m_pItemPicker || m_pUIInventory;
}

void PlayerAni::Pick(Item& item)
{
    switch (item.GetItemTag())
    {
    case ITEM_TAG::Gun:
        {
            Gun* g = static_cast<Gun*>(&item);
            if (m_mapGuns.find(g->GetGunTag()) == m_mapGuns.end()) //Add the gun to the equipment list if it does not exist
                PutGunInEquip(g);
            else
                PutItemInInventory(&item);
        }
        break;
    default:
        PutItemInInventory(&item);
        break;
    }
}

PlayerAniCollisionListener::PlayerAniCollisionListener(BaseObject& owner)
	: ICollisionListener(owner)
{
}

void PlayerAniCollisionListener::OnCollisionEnter(const ColliderBase& other)
{
    switch (other.GetTag())
    {
    case CollisionTag::kEnemy:
        {
            BaseObject* owner = GetOwner();
            PlayerAni* player = static_cast<PlayerAni*>(owner);

            if (!player->IsGameOver())
            {
                player->DiedAni();

                IDisplayObject* e = g_pObjMgr->FindObjectByTag(TAG_CUBEMAN_BARRACK);
                CubemanBarrack* cb = static_cast<CubemanBarrack*>(e);

                UIGameOver* uigo = new UIGameOver;
                uigo->Init(false, cb->GetNumCubemans() + 1, 4);
                g_pUIManager->RegisterUIObject(*uigo);
            }
        }
        break;
    }
}

void PlayerAniCollisionListener::OnCollisionExit(const ColliderBase& other)
{
}

void PlayerAniCollisionListener::OnCollisionStay(const ColliderBase& other)
{
}

/* 디버그용 */
void PlayerAni::ShowInventoryForDebug()
{
    Debug->AddText("<Guns list>");
    Debug->EndLine();
    for (auto item : m_mapGuns)
    {
        auto itemTag = item.first;
        switch (itemTag)
        {
        case GUN_TAG::Pistol:
            Debug->AddText("- Pistol, ");
            ShowItemStateForDebug(item.second->GetItemState());
            Debug->EndLine();
            break;
        case GUN_TAG::Rifle:
            Debug->AddText("- Rifle, ");
            ShowItemStateForDebug(item.second->GetItemState());
            Debug->EndLine();
            break;
        }
    } //for m_mapGuns

    Debug->EndLine();
    Debug->AddText("<Inventory>");
    Debug->EndLine();
    Debug->AddText("the number of Items: ");
    Debug->AddText(GetInventorySize() + GetGunsNum());
    Debug->EndLine();
    for (auto item : m_mapInventory)
    {
        auto itemTag = item.first;
        switch (itemTag)
        {
        case ITEM_TAG::Bullet:
            Debug->AddText("- Bullet: ");
            Debug->AddText(item.second.size());
            Debug->EndLine();

            for (auto i : item.second)
            {
                switch (static_cast<Bullet*>(i)->GetBulletFor())
                {
                case GUN_TAG::Pistol:
                    Debug->AddText("for Pistol, ");
                    break;
                case GUN_TAG::Rifle:
                    Debug->AddText("for Rifle, ");
                    break;
                }
                ShowItemStateForDebug(i->GetItemState());
                Debug->EndLine();
            } // for item.second()
            break;
        } //switch itemTag
    } //for m_mapInventory
}

void PlayerAni::ShowFireModeForDebug()
{
    Debug->EndLine();
    Debug->AddText("<Fire Mode>");
    switch (m_fireMode)
    {
    case FIRE_MODE::SingleShot:
        Debug->AddText("Single Mode");
        Debug->EndLine();
        break;

    case FIRE_MODE::Burst:
        Debug->AddText("Burst Mode");
        Debug->EndLine();
        break;

    }
}

void PlayerAni::ShowItemStateForDebug(ITEM_STATE itemState)
{
    switch (itemState)
    {
    case ITEM_STATE::Dropped:
        Debug->AddText("Dropped");
        break;
    case ITEM_STATE::InInventory:
        Debug->AddText("InInventory");
        break;
    case ITEM_STATE::Equipped:
        Debug->AddText("Equipped");
        break;
    case ITEM_STATE::InHand:
        Debug->AddText("In Hand");
        break;
    } //swtich ItemState
}

void PlayerAni::SetIsGameOver(const bool val)
{
    m_isGameOver = val;
}

bool PlayerAni::IsGameOver() const
{
    return m_isGameOver;
}
