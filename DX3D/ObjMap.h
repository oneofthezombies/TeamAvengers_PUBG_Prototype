#pragma once
#include "IMap.h"

class DrawingGroup;

class ObjMap : public IMap
{
private:
	vector<DrawingGroup*>	m_vecDrawingGroup;
	LPD3DXMESH				m_pMeshMap;
	vector<MTLTEX*>			m_vecMtlTex;

	float					m_rayOffsetY;

public:
	ObjMap();
	~ObjMap();

	// IMap을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual bool GetHeight(OUT float &height,
		const D3DXVECTOR3 &pos) override;
	virtual bool CalcPickedPosition(D3DXVECTOR3 &vOut,
		WORD screenX, WORD screenY) override { return true; }

	void RenderDrawingGroup();
	void RenderMesh();
	void RenderEachSubset();
	void RenderDrawSpeed();
};

