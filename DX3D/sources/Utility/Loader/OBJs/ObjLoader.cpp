#include "stdafx.h"
#include "ObjLoader.h"
#include "DrawingGroup.h"

ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

void ObjLoader::Load(const char * filePath, const char * fileName, D3DXMATRIX * pMat, OUT vector<DrawingGroup*>& vecGroup)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<VERTEX_PNT> vecPNT;
	string mtlName;

	char szToken[128];
	std::ifstream fin;

	m_filePath = filePath;
	string fullPath = m_filePath + "/" + fileName;

	fin.open(fullPath);

	if (fin.is_open() == false)
		return;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "mtllib"))
		{
			string fileName;
			fin >> fileName;
			fileName = m_filePath + "/" + fileName;

			LoadMtlLib(fileName.c_str());
		}
		else if (CompareStr(szToken, "g"))
		{
			if (vecPNT.empty()) continue;

			DrawingGroup* pGroup = new DrawingGroup;
			pGroup->SetVertexBuffer(vecPNT);
			pGroup->SetMtlTex(m_mapMtlTex[mtlName]);
			m_mapMtlTex[mtlName]->AddRef();
			vecGroup.push_back(pGroup);

			vecPNT.clear();
		}
		else if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "vt"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(szToken, "vn"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "usemtl"))
		{
			fin >> szToken;
			mtlName = szToken;
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3][3];
			fin.getline(szToken, 128);

			sscanf_s(szToken, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				VERTEX_PNT pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecPNT.push_back(pnt);
			}
		}
	}

	for (auto p : m_mapMtlTex)
		SAFE_RELEASE(p.second);

	m_mapMtlTex.clear();
	fin.close();
}

LPD3DXMESH ObjLoader::LoadMesh(const char * filePath, const char * fileName, D3DXMATRIX * pMat, OUT vector<MTLTEX*>& vecMtlTex)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<VERTEX_PNT> vecPNT;
	vector<DWORD> vecAttBuf;
	string mtlName;

	char szToken[128];
	std::ifstream fin;

	m_filePath = filePath;
	string fullPath = m_filePath + "/" + fileName;

	fin.open(fullPath);

	if (fin.is_open() == false)
		return NULL;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "mtllib"))
		{
			string fileName;
			fin >> fileName;
			fileName = m_filePath + "/" + fileName;

			LoadMtlLib(fileName.c_str());

			vecMtlTex.resize(m_mapMtlTex.size());
			for (auto p : m_mapMtlTex)
				vecMtlTex[p.second->id] = p.second;
		}
		/*else if (CompareStr(szToken, "g"))
		{
			if (vecPNT.empty()) continue;

			DrawingGroup* pGroup = new DrawingGroup;
			pGroup->SetVertexBuffer(vecPNT);
			pGroup->SetMtlTex(m_mapMtlTex[mtlName]);
			m_mapMtlTex[mtlName]->AddRef();
			vecGroup.push_back(pGroup);

			vecPNT.clear();
		}*/
		else if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "vt"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(szToken, "vn"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "usemtl"))
		{
			fin >> szToken;
			mtlName = szToken;
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3][3];
			fin.getline(szToken, 128);

			sscanf_s(szToken, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				VERTEX_PNT pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecPNT.push_back(pnt);
			}
			vecAttBuf.push_back(m_mapMtlTex[mtlName]->id);
		}
	}
	/*
	for (auto p : m_mapMtlTex)
		SAFE_RELEASE(p.second);
		*/
	m_mapMtlTex.clear();
	fin.close();

	//Mesh 생성 및 정보 채우기, 최적화
	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecPNT.size() / 3, vecPNT.size(), D3DXMESH_MANAGED,
		VERTEX_PNT::FVF, g_pDevice, &pMesh);

	VERTEX_PNT* pV = NULL;
	DWORD flags = 0;
	pMesh->LockVertexBuffer(flags, (LPVOID*)&pV);
	memcpy(pV, &vecPNT[0], vecPNT.size() * sizeof(VERTEX_PNT));
	pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
	pMesh->LockIndexBuffer(flags, (LPVOID*)&pI);
	for (size_t i = 0; i < vecPNT.size(); i++)
		pI[i] = static_cast<WORD>(i);
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(flags, &pA);
	memcpy(pA, &vecAttBuf[0], vecAttBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdjcency(pMesh->GetNumFaces() * 3);
	pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjcency[0]);
	
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE, &vecAdjcency[0], 0, 0, 0);

	return pMesh;
}

void ObjLoader::LoadSurface(const char * fullPath,
	D3DXMATRIX * pMat, OUT vector<D3DXVECTOR3>& vecVertex)
{
	vector<D3DXVECTOR3> vecP;
	
	char szToken[128];
	std::ifstream fin;

	fin.open(fullPath);

	if (fin.is_open() == false)
		return;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3];
			fin.getline(szToken, 128);

			sscanf_s(szToken, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; i++)
			{
				D3DXVECTOR3 v = vecP[aIndex[i] - 1];
				
				if (pMat)
				{
					D3DXVec3TransformCoord(&v, &v, pMat);
				}
				vecVertex.push_back(v);
			}
		}
	}

	fin.close();
}

void ObjLoader::LoadMtlLib(string fullPath)
{
	string mtlName;
	DWORD mtltexID = 0;
	char szToken[128];
	std::ifstream fin;

	fin.open(fullPath);
	
	if (fin.is_open() == false)
		return;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "newmtl"))
		{
			fin >> mtlName;

			SAFE_RELEASE(m_mapMtlTex[mtlName]);
			m_mapMtlTex[mtlName] = new MTLTEX;
			m_mapMtlTex[mtlName]->id = mtltexID++;
		}
		else if (CompareStr(szToken, "Ka"))
		{
			D3DCOLORVALUE c;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Ambient = c;
		}
		else if (CompareStr(szToken, "Kd"))
		{
			D3DCOLORVALUE c;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Diffuse = c;
		}
		else if (CompareStr(szToken, "Ks"))
		{
			D3DCOLORVALUE c;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Specular = c;
		}
		else if (CompareStr(szToken, "map_Kd"))
		{
			string filename;
			fin >> filename;
			filename = m_filePath + "/" + filename;

			m_mapMtlTex[mtlName]->SetTexture(
				g_pTextureManager->GetTexture(filename));
		}
	}

	fin.close();
}

bool ObjLoader::CompareStr(char * str1, const char * str2)
{
	return strcmp(str1, str2) == 0;
}
