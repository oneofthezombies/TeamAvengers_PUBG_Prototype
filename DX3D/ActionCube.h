#pragma once
#include "IActionObject.h"

class ActionCube : public IActionObject
{
private:
	vector<VERTEX_PC>		m_vecVertex;
	vector<WORD>			m_vecIndex;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	D3DVERTEXBUFFER_DESC	m_VBDesc;
	D3DINDEXBUFFER_DESC		m_IBDesc;

	D3DXVECTOR3				m_prevPos;
	D3DXVECTOR3				m_forward;

public:
	ActionCube();
	~ActionCube();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void InitVertex();
	void SetVertex(vector<VERTEX_PC> &vecVertexOut,
		vector<WORD> &vecIndexOut, vector<D3DXVECTOR3> vecPos);
	void SetBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb,
		LPDIRECT3DINDEXBUFFER9 &pIb,
		vector<VERTEX_PC> &vecVertex, vector<WORD> &vecIndex);

	void LookForward(D3DXVECTOR3 &outVec3, D3DXMATRIXA16 &outMat);
};

