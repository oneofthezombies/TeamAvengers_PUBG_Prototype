#include "stdafx.h"
#include "AStarNode.h"


AStarNode::AStarNode(D3DXVECTOR3 location, int index)
{
	m_location = location;
	m_index = index;

	SetValue(STATE_NONE, 0, 0, 0, 0);
}

AStarNode::~AStarNode()
{
}

void AStarNode::SetValue(NODE_STATE _nodeState, float _g, float _h, float _f, int _via)
{
	m_nodeState = _nodeState;
	m_g = _g;
	m_h = _h;
	m_f = _f;
	m_via = _via;
}

void AStarNode::AddEdge(AStarNode* pNode)
{
	EDGE_INFO* edgeInfo = new EDGE_INFO;
	edgeInfo->index = pNode->m_index;
	edgeInfo->edgeCost = D3DXVec3Length(&(m_location - pNode->m_location));

	m_vecEdgeInfo.push_back(edgeInfo);

	m_vecLine.push_back(this->m_location);
	m_vecLine.push_back(pNode->m_location);
}
