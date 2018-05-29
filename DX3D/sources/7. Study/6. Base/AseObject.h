#pragma once
#include "BaseObject.h"

class AseObject : public BaseObject
{
public:
	D3DXMATRIX		m_matLocalTM;
	D3DXMATRIX		m_matWorldTM;
	vector<AseObject*>	m_vecChild;
	vector<VERTEX_PNT>	m_vecVertex;
	LPDIRECT3DTEXTURE9	m_pTex;
	D3DMATERIAL9		m_mtl;
	string				m_texName;
	vector<ASE_POS_SAMPLE> m_vecPosTrack;
	vector<ASE_ROT_SAMPLE> m_vecRotTrack;

	AseObject();
	~AseObject();

	void Init();
	void Update(int tickCount, D3DXMATRIX* pMatParent);
	void Render();
	void AddChild(AseObject* pChild);
	void ReleaseAll();
	void SetupTexture();
	void CalcLocalTM(AseObject* pParent = NULL);
	void CalcLocalTranslationMatrix(IN int tickCount,
		OUT D3DXMATRIX& mat);
	void CalcLocalRotationMatrix(IN int tickCount, 
		OUT D3DXMATRIX& mat);
};

