#pragma once
#include "IDisplayObject.h"
class Frustum :
	public IDisplayObject
{
	vector<D3DXVECTOR3> m_vecProjVtx;
	vector<D3DXVECTOR3> m_vecWorldVtx;
	vector<D3DXPLANE>   m_vecPlane;
	vector<BoundingSphere*> m_vecpBoundary;
	LPD3DXMESH			m_pMesh;
public:
	Frustum();
	~Frustum();

	// Inherited via IDisplayObject
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void UpdateFrustum();
	bool IsSphereInsideFrustum(BoundingSphere* pSphere);
};

