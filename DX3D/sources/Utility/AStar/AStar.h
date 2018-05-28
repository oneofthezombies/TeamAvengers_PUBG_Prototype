#pragma once
#include "BaseObject.h"
class AStarNode;
class Heap;
class AStar :public BaseObject
{
private:
	vector<AStarNode*> m_vecNode;
	list<AStarNode*>   m_pOpenNodeList;	//heap 용도로 쓸것임/ 이곳에서 open된 것들 관리
	Heap*			   m_pOpenNodeHeap;
	LPD3DXMESH		   m_pSphere;
	vector<D3DXVECTOR3> m_vecObstacle; //장애물의 position

public:
	AStar();
	virtual ~AStar();

	void Init();
	void Render(); //노드들 색변하고, 선 그려주는 것을 하는 부분
	void InitNode(IMap* pMap); //map의 크기를 참조해 와서 setting 해주는 부분
	const vector<AStarNode*>& GetNodes() { return m_vecNode; }
	void SetObstacle(const vector<D3DXVECTOR3> &vecObstacle)
	{
		m_vecObstacle = vecObstacle;
	}
	void FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int>& vecIndex);//따라갈 목록을 이곳에 저장해 주는 부분

private:
	void RestNodes();	//시작시 노드들을 초기화 해주는 부분
	int FindClosestNode(const D3DXVECTOR3 &pos);	//position에서 가장 가까운 노드들 찾는
	float GetManHattanDistance(int from, int to);	//from 에서 to 까지 멘하탄 distance
	int GetMinFNodeIndex();							//가장 작은 F 노드의 Index를 반환 
	void Extend(int targetIdx, int destIdx);		//확장

public:
	void MakeDirectPath(const D3DXVECTOR3 &startPos, const D3DXVECTOR3 &destPos, OUT vector<int>& vecIndex);
private:
	void CalcEraseCount(const D3DXVECTOR3& pos, const vector<int>& vecIndex, bool bByStartPos, OUT int &numEraseNode);

};

