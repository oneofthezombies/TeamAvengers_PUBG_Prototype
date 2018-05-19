#pragma once

class DrawingGroup;

class ObjLoader
{
public:
	string		m_filePath;
	map<string, MTLTEX*> m_mapMtlTex;

	ObjLoader();
	~ObjLoader();

	void Load(const char* filePath, const char* fileName,
		D3DXMATRIXA16 *pMat, OUT vector<DrawingGroup*> &vecGroup);
	LPD3DXMESH LoadMesh(const char* filePath, const char* fileName,
		D3DXMATRIXA16 *pMat, OUT vector<MTLTEX*> &vecMtlTex);
	void LoadSurface(const char* fullPath, D3DXMATRIXA16* pMat,
		OUT vector<D3DXVECTOR3> &vecVertex);
	void LoadMtlLib(string fullPath);
	bool CompareStr(char* str1, const char* str2);
};

