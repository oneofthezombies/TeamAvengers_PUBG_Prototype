#pragma once

class AseObject;

class AseLoader
{
private:
	std::ifstream			m_fin;
	char					m_szToken[512];
	vector<D3DMATERIAL9>	m_vecMtl;
	vector<string>			m_vecTexName;
	map<string, AseObject*> m_mapAseObject;

public:
	AseLoader();
	~AseLoader();

	AseObject*	Load(const char* fullPath, OUT ASE_SCENE* pScene);
	char*		GetToken();
	int			GetTokenAsInt();
	float		GetTokenAsFloat();
	bool		CompareStr(char* str1, const char* str2);

	void		ProcessSCENE(OUT ASE_SCENE* pScene);
	void		ProcessMATERIAL_LIST();
	void		ProcessMATERIAL(int index);
	void		ProcessMAP_DIFFUSE(int index);
	AseObject*	ProcessGEOMOBJECT(OUT AseObject* &pObj);
	void		ProcessNODE_TM(OUT AseObject* &pObj);
	void		ProcessMESH(OUT AseObject* &pObj);
	void		ProcessMESH_VERTEX_LIST(OUT vector<D3DXVECTOR3>& vecP);
	void		ProcessMESH_FACE_LIST(IN vector<D3DXVECTOR3>& vecP,
		OUT vector<VERTEX_PNT>& vecVertex);
	void		ProcessMESH_TVERTLIST(OUT vector<D3DXVECTOR2> & vecT);
	void		ProcessMESH_TFACELIST(IN vector<D3DXVECTOR2>& vecT,
		OUT vector<VERTEX_PNT> & vecVertex);
	void		ProcessMESH_NORMALS(OUT vector<VERTEX_PNT>& vecVertex);
	void		ProcessTM_ANIMATION(OUT AseObject* &pObj);
	void		ProcessPOS_TRACK(OUT AseObject* &pObj);
	void		ProcessROT_TRACK(OUT AseObject* &pObj);

};

