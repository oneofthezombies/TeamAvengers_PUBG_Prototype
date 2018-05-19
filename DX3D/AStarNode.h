#pragma once
#include "BaseObject.h"

// 현재 노드의 이웃노드 정보
struct EDGE_INFO
{
    int index;

	// 내 노드로부터 이웃노드까지의 비용(거리)
	float edgeCost;
};

enum NODE_STATE
{
	STATE_NONE,
	STATE_OPEN,
	STATE_CLOSE,
	STATE_USING,
	STATE_WALL 
};

class AStarNode :public BaseObject
{//astarnode가 EDGE_INFO를 배열로 갖고 있어서
public:
	D3DXVECTOR3 m_location;
	int			m_index;
	NODE_STATE  m_nodeState;
	float		m_g;	// 시작점으로부터의 코스트
	float		m_h;	// 도착점까지의 코스트
	float		m_f;	// g + h
	int			m_via; //이전노드가 어떤것인지 저장하는 부분

	vector<EDGE_INFO*>		m_vecEdgeInfo; // 최대 8개
	vector<D3DXVECTOR3>		m_vecLine; // 드로잉용

	AStarNode(D3DXVECTOR3 location, int index);
	virtual ~AStarNode();

	void SetValue(NODE_STATE _nodeState, float _g, float _h, float _f, int _via);
	void AddEdge(AStarNode* pNode);
	const D3DXVECTOR3& GetLocation() { return m_location; }
	const vector<D3DXVECTOR3>& GetVecLines() { return m_vecLine; }
	const vector<EDGE_INFO*>& GetEdgeInfos() { return m_vecEdgeInfo; }

};

