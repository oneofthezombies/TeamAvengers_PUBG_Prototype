#include "stdafx.h"
#include "PlayerTemp.h"
#include "Pistol.h"
#include "Bullet.h"

PlayerTemp::PlayerTemp()
	: m_pPlayerMesh(nullptr)
	, m_velocity(5.f)
	, m_isRun(false)
	, m_pPistol(nullptr)
{
}

PlayerTemp::~PlayerTemp()
{
	SAFE_RELEASE(m_pPlayerMesh);
}

void PlayerTemp::Init()
{
	m_pos = D3DXVECTOR3(0.f, 3.f, -20.f);                          //일단 하드코딩으로 위치 박음
	D3DXCreateBox(g_pDevice, 2.f, 6.f, 2.f, &m_pPlayerMesh, NULL); //임시 플레이어 메쉬 생성 (임시로 박스 모양)
}

void PlayerTemp::Update()
{
	KeyMove();    //이동
	KeyMount();   //장착
	KeyUnmount(); //장착해제
	KeyLoad();    //총 장전
	KeyFire();    //총 쏘기

	//변환행렬 재설정
	D3DXMatrixTranslation(&m_matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = m_matT;

	/* 디버그 */
	//인벤토리 디버그용
	ShowInventoryForDebug();

	//총알 개수 디버그용
	if (m_pPistol)
		m_pPistol->ShowBulletNumForDebug();
}

void PlayerTemp::Render()
{
	const auto dv = g_pDevice;
	dv->SetRenderState(D3DRS_LIGHTING, false);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	dv->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pPlayerMesh->DrawSubset(0);

	dv->SetRenderState(D3DRS_LIGHTING, true);
	dv->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void PlayerTemp::PutItemInInventory(Item* item)
{
	item->SetItemState(ITEM_STATE::InInventory);
	m_mapInventory[item->GetItemTag()].push_back(item);
}
void PlayerTemp::ShowInventoryForDebug()
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
void PlayerTemp::KeyMove()
{
	float deltaTime = g_pTimeManager->GetDeltaTime();
	float distance = deltaTime * m_velocity;

	/* 이동 ASDW */ // 맵 구역 안에 있을 때만 움직인다 
	if (g_pKeyManager->IsStayKeyDown('A')) //왼쪽
	{
		if (m_pos.x - distance >= -5.f)
			m_pos.x -= distance;
	}
	if (g_pKeyManager->IsStayKeyDown('D')) //오른쪽
	{
		if (m_pos.x + distance <= 5.f)
			m_pos.x += distance;
	}
	if (g_pKeyManager->IsStayKeyDown('W')) //위쪽
	{
		if (m_pos.z + distance <= 20.f)
			m_pos.z += distance;
	}
	if (g_pKeyManager->IsStayKeyDown('S')) //아래쪽
	{
		if (m_pos.z - distance >= -20.f)
			m_pos.z -= distance;
	}

	/* 총 장착시 총 위치 업데이트 */
	if (m_pPistol)
	{
		m_pPistol->SetPosition(&D3DXVECTOR3(m_pos.x, m_pos.y + 1.f, m_pos.z + 2.f)); //플레이어보다 살짝 위, 살짝 앞
	}
}

void PlayerTemp::KeyMount()
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
					m_pPistol = static_cast<Pistol*>(item.second.front());
					m_pPistol->SetItemState(ITEM_STATE::Mounting); //장착중
					std::cout << "장착 완료" << std::endl;
					break; //총한개만 찾지롱
				}
			}
		}
	}
}

void PlayerTemp::KeyUnmount()
{
	/* 무기 장착 해제 */
	if (g_pKeyManager->IsOnceKeyDown('X'))
	{
		if (m_pPistol)
		{
			m_pPistol->SetItemState(ITEM_STATE::InInventory); //장착해제중
			m_pPistol = nullptr;
			std::cout << "장착 해제" << std::endl;
		}
	}

}

void PlayerTemp::KeyLoad()
{
	/* 총알 장전 */
	if (g_pKeyManager->IsOnceKeyDown('R'))
	{
		if (m_pPistol) //장착하고 있는 총이 있으면
		{
			//총알 찾기
			for (auto item : m_mapInventory)
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

void PlayerTemp::KeyFire()
{
	/* 총쏘기 SPACE */ //TODO: 마우스 왼쪽 버튼으로 바꿔야함!!
	if (g_pKeyManager->IsOnceKeyDown(VK_SPACE))
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
