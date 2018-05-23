#pragma once
#include "IDisplayObject.h"

class CubemanParts : public IDisplayObject
{
private:
	vector<VERTEX_PC>	m_vecPCVertex;
	vector<VERTEX_PT>	m_vecPTVertex;
	
	bool				m_isMoving;
	float				m_rotXAngle;
	float				m_rotXSpeed;

	LPDIRECT3DTEXTURE9	m_tex;

public:
	CubemanParts(float rotXSpeed = 0.0f);
	~CubemanParts();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Init(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV);
	void SetPCVertex(vector<VERTEX_PC> &vecOut,
		vector<D3DXVECTOR3> &vecVertex);
	void SetPTVertex(vector<VERTEX_PT> &vecOut, 
		vector<D3DXVECTOR3> &vecVertex, vector<vector<int>> &uv);
	void SetMovingState(bool isMoving);
	void MakeUVList(vector<D3DXVECTOR2> &out, 
		vector<vector<int>> &uv);
};

