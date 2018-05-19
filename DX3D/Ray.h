#pragma once
class Ray
{
public:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_dir;

	Ray();
	~Ray();

	static Ray RayAtViewSpace(int x, int y);
	static Ray RayAtWorldSpace(int x, int y);

	bool CalcIntersectSphere(BoundingSphere* pSphere);
	bool CalcIntersectTri(D3DXVECTOR3* pStart, float *distance);
};

