#pragma once
#include "BaseObject.h"

class DrawingGroup : public BaseObject
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	size_t					m_numTri;
	MTLTEX*					m_MtlTex;

public:
	DrawingGroup();
	~DrawingGroup();

	void SetMtlTex(MTLTEX* p) { m_MtlTex = p; }
	void SetVertexBuffer(const vector<VERTEX_PNT> &vec);
	void Render();
};

