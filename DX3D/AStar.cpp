#include "stdafx.h"
#include "AStar.h"
#include "AStarNode.h"
#include "Ray.h"
#include "Heap.h"
#include "IMap.h"
#include "D3DUtility.h"

AStar::AStar()
{
}


AStar::~AStar()
{
	SAFE_DELETE(m_pOpenNodeHeap);
	SAFE_RELEASE(m_pSphere);
	for (auto p : m_vecNode)
		SAFE_RELEASE(p);
}

void AStar::Init()
{
	float radius = 0.2f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);
	m_pOpenNodeHeap = new Heap;
	//InitNode(g_pMapManager->GetCurrentMap());
}

void AStar::Render()
{
	D3DXMATRIX mat;
	g_pDevice->SetTexture(0, NULL);

	for (auto p : m_vecNode)
	{
		switch (p->m_nodeState)
		{
		case STATE_NONE:
			g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
			break;
		case STATE_OPEN:
			g_pDevice->SetMaterial(&DXUtil::GREEN_MTRL);
			break;
		case STATE_CLOSE:
			g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
			break;
		case STATE_USING:
			g_pDevice->SetMaterial(&DXUtil::YELLOW_MTRL);
			break;
		case STATE_WALL:
			g_pDevice->SetMaterial(&DXUtil::BLUE_MTRL);
			break;
		}
		
		D3DXMatrixTranslation(&mat,p->GetLocation().x, p->GetLocation().y, p->GetLocation().z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pSphere->DrawSubset(0);

		D3DXMatrixIdentity(&mat);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, p->GetVecLines().size() / 2, p->GetVecLines()[0], sizeof(D3DXVECTOR3));
	}
}

void AStar::InitNode(IMap* pMap)
{
	int nodeDim = 30;
	float interval = pMap->GetSize().x / (float)(nodeDim - 0.99f);//1주면 터져서.. map size 끝까지 하기 위해

	for (int posZ = 0; posZ < nodeDim; posZ++)
	{
		for (int posX = 0; posX < nodeDim; posX++)
		{
			D3DXVECTOR3 location(posX*interval, 0, posZ*interval);
			pMap->GetHeight(location.y, location);

			AStarNode* pNode = new AStarNode(location, m_vecNode.size() /*posX + posZ * nodeDim*/);
			m_vecNode.push_back(pNode);

			if (posX == 2 && posZ < 5)
			{
				pNode->m_nodeState = STATE_WALL;
			}
		}
	}

	for (size_t i = 0; i < m_vecNode.size(); i++)
	{
		//제일 우측 열을 제외하고 자신의 우측 노드와 서로 Edge 등록
		if (i % nodeDim/*pos x*/ != nodeDim - 1)
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + 1]);
			m_vecNode[i + 1]->AddEdge(m_vecNode[i]);
		}
		//제일 윗 횡을 제외하고 자신의 윗 노드와 서로 Edge 등록
		if (i < m_vecNode.size() - nodeDim)
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + nodeDim]);
			m_vecNode[i + nodeDim]->AddEdge(m_vecNode[i]);
		}
	}

	/*
	i = x + dim * z 2차원에서 1차원으로
	i % dim = x 1차원에서 2차원으로
	*/
}

void AStar::FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int>& vecIndex)
{
	RestNodes();
	
	int startNodeIdx = FindClosestNode(startPos);	//시작노드 찾기
	int destNodeIdx = FindClosestNode(destPos);		//마지막 노드 찾기

	if (startNodeIdx == -1 || destNodeIdx == -1)
		return; //없으면 종료

	//출발지 노드를 초기화 해주고 열림 상태로 만든다
	float g = 0.0f;
	float h = GetManHattanDistance(startNodeIdx, destNodeIdx);
	float f = g + h;

	m_vecNode[startNodeIdx]->SetValue(STATE_OPEN, g, h, f, startNodeIdx);
	//m_pOpenNodeList.push_back(m_vecNode[startNodeIdx]);//현재 open list에 하나가 있다. 이제 목적지까지 넣어서 사용
	m_pOpenNodeHeap->Insert(m_vecNode[startNodeIdx]);

	//목적지 노드가 닫힘 사 될 때까지 출발지 노드부터 확장해 나간다
	//확장을 완료한 노드는 닫힘 상태로 만든다
	while (m_vecNode[destNodeIdx]->m_nodeState != STATE_CLOSE)
	{
		int currIndex = GetMinFNodeIndex();
		if (currIndex == -1) return;

		Extend(currIndex, destNodeIdx);
		m_vecNode[currIndex]->m_nodeState = STATE_CLOSE;
	}
	//이제 길을 다 찾은 상태

	//목적지 노드부터 출발지 노드 이전 까지 경유 노드들의 인덱스를 path 목록에 추가
	//목록에 추가한 노드들은 사용 상태로 만든다
	int currIndex = destNodeIdx;
	while (currIndex != startNodeIdx)
	{
		m_vecNode[currIndex]->m_nodeState = STATE_USING;
		vecIndex.push_back(currIndex);
		currIndex = m_vecNode[currIndex]->m_via;//via는 자기 이전 노드에 대한 index
	}
	//출발지 노드의 인덱스도 Path 목록에 추가하고 사용 상태로 만든다
	m_vecNode[currIndex]->m_nodeState = STATE_USING;
	vecIndex.push_back(currIndex);
	
	//이 리스트는 
	//목적지 -> 경유지 .... -> 출발지 인덱스 목록 완성

	//m_pOpenNodeList.clear();
	m_pOpenNodeHeap->Clear();
}

void AStar::RestNodes()
{
	for (size_t i = 0u; i < m_vecNode.size(); i++)
	{
		if (m_vecNode[i]->m_nodeState != STATE_WALL)
			m_vecNode[i]->m_nodeState = STATE_NONE;
	}
}

int AStar::FindClosestNode(const D3DXVECTOR3& pos)
{
	float minDist = FLT_MAX;
	int closestNodeIndex = -1;

	for (size_t i = 0u; i < m_vecNode.size(); i++)
	{
		if (m_vecNode[i]->m_nodeState == STATE_WALL)//장애물 노드는 무시하고
			continue;

		D3DXVECTOR3 subtract = pos - m_vecNode[i]->GetLocation();

		float dist = D3DXVec3Length(&subtract);
		if (dist < minDist)
		{
			minDist = dist;
			closestNodeIndex = i;
		}
	}
	return closestNodeIndex;	//걸린애가 없으면 -1 return된다.
}

float AStar::GetManHattanDistance(int from, int to)
{
	float offsetX = fabs(m_vecNode[from]->GetLocation().x - m_vecNode[to]->GetLocation().x);
	float offsetZ = fabs(m_vecNode[from]->GetLocation().z - m_vecNode[to]->GetLocation().z);
	return offsetX + offsetZ;
}		   

int AStar::GetMinFNodeIndex()
{
	AStarNode* node = NULL;
	
	/*
	float minValue = FLT_MAX;
	for (auto p : m_pOpenNodeList)
	{
		if (p->m_f < minValue)
		{
			minValue = p->m_f;
			node = p;
		}
	}
	if (node == NULL) 
		return -1;
	m_pOpenNodeList.remove(node);*/
	node = m_pOpenNodeHeap->ExtractMin();
	if (node == NULL) return -1;
	return node->m_index;
}

void AStar::Extend(int targetIdx, int destIdx)
{
	vector<EDGE_INFO*> vecEdge = m_vecNode[targetIdx]->GetEdgeInfos();

	for (size_t i = 0u; i < vecEdge.size(); i++)
	{
		int index = vecEdge[i]->index;
		AStarNode* currNode = m_vecNode[index];

		if (currNode->m_nodeState == STATE_CLOSE) continue;//닫힌 노드이거나
		if (currNode->m_nodeState == STATE_WALL) continue;//장애물일 시에 추가해 주지 않는 것

		float G = m_vecNode[targetIdx]->m_g + vecEdge[i]->edgeCost;
		float H = GetManHattanDistance(index, destIdx);
		float F = G + H;

		if (currNode->m_nodeState == STATE_OPEN && G >= currNode->m_g) continue;

		currNode->SetValue(STATE_OPEN, G, H, F, targetIdx);
		//m_pOpenNodeList.push_back(currNode);
		m_pOpenNodeHeap->Insert(currNode);
	}
}

void AStar::MakeDirectPath(const D3DXVECTOR3 & startPos, const D3DXVECTOR3 & destPos, OUT vector<int>& vecIndex)
{
	//장애물 없으면 노드 잘라내기
	if (m_vecObstacle.empty() == true)
	{
		//장애물이 없으면 직선으로 이동
		vecIndex.clear();
	}
	else
	{
		int numNodeToErase = 0;
		//시작 지점부터 장애물 교차 이전 지점까지 노드 삭제
		CalcEraseCount(startPos/*캐릭터위치*/, vecIndex, true, numNodeToErase);
		if (numNodeToErase > 0)
			vecIndex.erase(vecIndex.end() - numNodeToErase, vecIndex.end());

		//마지막 지점부터 장애물 교차 이전 지점까지 노드 삭제
		CalcEraseCount(destPos/*마우스포인터로 찝은 공간상의 위치*/, vecIndex, false, numNodeToErase);
		if (numNodeToErase == vecIndex.size()) numNodeToErase--;
		if (numNodeToErase > 0)
			vecIndex.erase(vecIndex.begin(), vecIndex.begin() + numNodeToErase);

	}
}

void AStar::CalcEraseCount(const D3DXVECTOR3 & pos, const vector<int>& vecIndex, bool bByStartPos, OUT int & numEraseNode)
{
	numEraseNode = 0;
	Ray ray;
	ray.m_pos = pos;
	ray.m_pos.y += 0.3f;

	for (size_t index = 0; index < vecIndex.size(); index++)
	{
		if (bByStartPos == true)
		{
			int theLast = vecIndex.size() - 1;
			int last = theLast - index;
			int node_i = vecIndex[last];
			ray.m_dir = m_vecNode[node_i]->GetLocation() - pos;
		}
		else
		{
			ray.m_dir = m_vecNode[vecIndex[index]]->GetLocation() - pos;
		}
		float nodeDist = D3DXVec3Length(&ray.m_dir);
		D3DXVec3Normalize(&ray.m_dir, &ray.m_dir);
		float intersectionDist;
		bool isIntersected = false;

		for (size_t i = 0; i < m_vecObstacle.size(); i += 3)
		{
			if (ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
			{
				if (intersectionDist < nodeDist)
				{
					isIntersected = true;
					break;
				}
			}
		}
		if (isIntersected == true)
		{
			numEraseNode--;
			break;
		}
		else
		{
			numEraseNode++;
		}
	}

}
