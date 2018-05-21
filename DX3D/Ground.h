#pragma once
#include "IDisplayObject.h"
class Ground : public IDisplayObject
{
private:
	DWORD                   m_numVertices;
	DWORD                   m_numIndices;

	LPDIRECT3DINDEXBUFFER9  m_pIB;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	int                     m_col; //격자의 가로개수
	int                     m_row; //격자의 세로개수
	float                   m_size;

public:
	Ground(int col, int row, float size);
	~Ground();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

