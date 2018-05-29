#include "stdafx.h"
#include "AseLoader.h"
#include "AseObject.h"
#include "Asciitok.h"

AseLoader::AseLoader()
{
}


AseLoader::~AseLoader()
{
}

AseObject * AseLoader::Load(const char * fullPath, OUT ASE_SCENE* pScene)
{
	m_fin.open(fullPath);

	if (m_fin.is_open() == false)
		return NULL;

	AseObject* m_pRootObj = NULL;

	while (m_fin.eof() == false)
	{
		char* szToken = GetToken();

		if (CompareStr(szToken, ID_SCENE))
		{
			if (pScene != NULL) ProcessSCENE(pScene);
		}
		else if (CompareStr(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (CompareStr(szToken, ID_GEOMETRY))
		{
			AseObject* pObj = new AseObject;
			ProcessGEOMOBJECT(pObj);
			if (m_pRootObj == NULL)
			{
				m_pRootObj = pObj;
				pObj->AddRef();
			}
			pObj->Release();
		}
	}

	m_fin.close();

	return m_pRootObj;
}

char * AseLoader::GetToken()
{
	bool isQuot = false;
	char szToken[512];

	do 
	{
		m_fin >> m_szToken;
		//" 가 나오면 " 가 다시 나올 때까지 문장을 묶는다
		if (m_szToken[0] == '\"' ||
			m_szToken[strlen(m_szToken) - 1] == '\"')
		{
			if (isQuot == true)
			{
				isQuot = false;
				strncat_s(szToken, " ", 1);
				strncat_s(szToken, m_szToken, strlen(m_szToken));
			}
			else
			{
				if (m_szToken[strlen(m_szToken) - 1] != '\"')
				{
					isQuot = true;
				}
				strcpy_s(szToken, m_szToken);
			}
		}
		else
		{
			if (isQuot == true)
			{
				strncat_s(szToken, " ", 1);
				strncat_s(szToken, m_szToken, strlen(m_szToken));
			}
			else
			{
				strcpy_s(szToken, m_szToken);
			}
		}
	} while (isQuot == true);
	
	strcpy_s(m_szToken, szToken);
	
	return m_szToken;
}

int AseLoader::GetTokenAsInt()
{
	return atoi(GetToken());
}

float AseLoader::GetTokenAsFloat()
{
	return static_cast<float>(atof(GetToken()));
}

bool AseLoader::CompareStr(char * str1, const char * str2)
{
	return strcmp(str1, str2) == 0;
}

void AseLoader::ProcessSCENE(OUT ASE_SCENE * pScene)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_FIRSTFRAME))
		{
			pScene->numFirstFrame = GetTokenAsInt();
		}
		else if (CompareStr(szToken, ID_LASTFRAME))
		{
			pScene->numLastFrame = GetTokenAsInt();
		}
		else if (CompareStr(szToken, ID_FRAMESPEED))
		{
			pScene->frameSpeed = GetTokenAsInt();
		}
		else if (CompareStr(szToken, ID_TICKSPERFRAME))
		{
			pScene->ticksPerFrame = GetTokenAsInt();
		}
	} while (level > 0);
}

void AseLoader::ProcessMATERIAL_LIST()
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_MATERIAL_COUNT))
		{
			int size = GetTokenAsInt();

			m_vecMtl.resize(size);
			m_vecTexName.resize(size);
		}
		else if (CompareStr(szToken, ID_MATERIAL))
		{
			ProcessMATERIAL(GetTokenAsInt());
		}
	} while (level > 0);
}

void AseLoader::ProcessMATERIAL(int index)
{
	D3DMATERIAL9* mtl = &m_vecMtl[index];
	ZeroMemory(mtl, sizeof(D3DMATERIAL9));

	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_AMBIENT))
		{
			mtl->Ambient.r = GetTokenAsFloat();
			mtl->Ambient.g = GetTokenAsFloat();
			mtl->Ambient.b = GetTokenAsFloat();
			mtl->Ambient.a = 1.0f;
		}
		else if (CompareStr(szToken, ID_DIFFUSE))
		{
			mtl->Diffuse.r = GetTokenAsFloat();
			mtl->Diffuse.g = GetTokenAsFloat();
			mtl->Diffuse.b = GetTokenAsFloat();
			mtl->Diffuse.a = 1.0f;
		}
		else if (CompareStr(szToken, ID_SPECULAR))
		{
			mtl->Specular.r = GetTokenAsFloat();
			mtl->Specular.g = GetTokenAsFloat();
			mtl->Specular.b = GetTokenAsFloat();
			mtl->Specular.a = 1.0f;
		}
		else if (CompareStr(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(index);
		}
	} while (level > 0);

}

void AseLoader::ProcessMAP_DIFFUSE(int index)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_BITMAP))
		{
			char* path = GetToken();
			path = &path[1];
			path[strlen(path) - 1] = '\0';

			m_vecTexName[index] = path;
		}
	} while (level > 0);
}

AseObject * AseLoader::ProcessGEOMOBJECT(OUT AseObject *& pObj)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_NODE_NAME))
		{
			char* nodeName = GetToken();
			m_mapAseObject[nodeName] = pObj;
		}
		else if (CompareStr(szToken, ID_NODE_PARENT))
		{
			char* parentName = GetToken();
			m_mapAseObject[parentName]->AddChild(pObj);
			pObj->AddRef();
		}
		else if (CompareStr(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pObj);
		}
		else if (CompareStr(szToken, ID_MESH))
		{
			ProcessMESH(pObj);
		}
		else if (CompareStr(szToken, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(pObj);
		}
		else if (CompareStr(szToken, ID_MATERIAL_REF))
		{
			int index = GetTokenAsInt();

			pObj->m_mtl = m_vecMtl[index];
			pObj->m_texName = m_vecTexName[index];
		}
	} while (level > 0);

	return pObj;
}

void AseLoader::ProcessNODE_TM(OUT AseObject *& pObj)
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetTokenAsFloat();
			matWorld._13 = GetTokenAsFloat();
			matWorld._12 = GetTokenAsFloat();
			matWorld._14 = 0.0f;
		}
		else if (CompareStr(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetTokenAsFloat();
			matWorld._33 = GetTokenAsFloat();
			matWorld._32 = GetTokenAsFloat();
			matWorld._34 = 0.0f;
		}
		else if (CompareStr(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetTokenAsFloat();
			matWorld._23 = GetTokenAsFloat();
			matWorld._22 = GetTokenAsFloat();
			matWorld._24 = 0.0f;
		}
		else if (CompareStr(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetTokenAsFloat();
			matWorld._43 = GetTokenAsFloat();
			matWorld._42 = GetTokenAsFloat();
			matWorld._44 = 1.0f;
		}
		
	} while (level > 0);

	pObj->m_matWorldTM = matWorld;
}

void AseLoader::ProcessMESH(OUT AseObject * &pObj)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<VERTEX_PNT> vecVertex;

	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_MESH_NUMVERTEX))
		{
			vecP.resize(GetTokenAsInt());
		}
		else if (CompareStr(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(3 * GetTokenAsInt());
		}
		else if (CompareStr(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecP);
		}
		else if (CompareStr(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecP, vecVertex);
		}
		else if (CompareStr(szToken, ID_MESH_NUMTVERTEX))
		{
			vecT.resize(GetTokenAsInt());
		}
		else if (CompareStr(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecT);
		}
		else if (CompareStr(szToken, ID_MESH_NUMTVFACES))
		{
			GetToken();
		}
		else if (CompareStr(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecT, vecVertex);
		}
		else if (CompareStr(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMALS(vecVertex);
		}
	} while (level > 0);

	D3DXMATRIX matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &pObj->m_matWorldTM);

	for (size_t i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p,
			&matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n,
			&matInvWorld);
	}

	pObj->m_vecVertex = vecVertex;
}

void AseLoader::ProcessMESH_VERTEX_LIST(OUT vector<D3DXVECTOR3>& vecP)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_MESH_VERTEX))
		{
			int index = GetTokenAsInt();
			vecP[index].x = GetTokenAsFloat();
			vecP[index].z = GetTokenAsFloat();
			vecP[index].y = GetTokenAsFloat();
		}
	} while (level > 0);
}

void AseLoader::ProcessMESH_FACE_LIST(IN vector<D3DXVECTOR3>& vecP, OUT vector<VERTEX_PNT>& vecVertex)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_MESH_FACE))
		{
			int faceIndex = GetTokenAsInt();
			GetToken();
			int nA = GetTokenAsInt();
			GetToken();
			int nB = GetTokenAsInt();
			GetToken();
			int nC = GetTokenAsInt();

			vecVertex[faceIndex * 3 + 0].p = vecP[nA];
			vecVertex[faceIndex * 3 + 1].p = vecP[nC];
			vecVertex[faceIndex * 3 + 2].p = vecP[nB];
		}
	} while (level > 0);
}

void AseLoader::ProcessMESH_TVERTLIST(OUT vector<D3DXVECTOR2>& vecT)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_MESH_TVERT))
		{
			int index = GetTokenAsInt();
			vecT[index].x = GetTokenAsFloat();
			vecT[index].y = 1.0f - GetTokenAsFloat();
		}
	} while (level > 0);
}

void AseLoader::ProcessMESH_TFACELIST(IN vector<D3DXVECTOR2>& vecT, OUT vector<VERTEX_PNT>& vecVertex)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_MESH_TFACE))
		{
			int faceIndex = GetTokenAsInt();
			int nA = GetTokenAsInt();
			int nB = GetTokenAsInt();
			int nC = GetTokenAsInt();

			vecVertex[faceIndex * 3 + 0].t = vecT[nA];
			vecVertex[faceIndex * 3 + 1].t = vecT[nC];
			vecVertex[faceIndex * 3 + 2].t = vecT[nB];
		}
	} while (level > 0);
}

void AseLoader::ProcessMESH_NORMALS(OUT vector<VERTEX_PNT>& vecVertex)
{
	int faceIndex = 0;
	int vertexCount = 0;
	int aVertexIndex[] = { 0, 2, 1 };

	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_MESH_FACENORMAL))
		{
			faceIndex = GetTokenAsInt();
			vertexCount = 0;
		}
		else if (CompareStr(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			vecVertex[faceIndex * 3 + aVertexIndex[vertexCount]].n.x = GetTokenAsFloat();
			vecVertex[faceIndex * 3 + aVertexIndex[vertexCount]].n.z = GetTokenAsFloat();
			vecVertex[faceIndex * 3 + aVertexIndex[vertexCount]].n.y = GetTokenAsFloat();
			vertexCount++;
		}
	} while (level > 0);
}

void AseLoader::ProcessTM_ANIMATION(OUT AseObject *& pObj)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_POS_TRACK))
		{
			ProcessPOS_TRACK(pObj);
		}
		else if (CompareStr(szToken, ID_ROT_TRACK))
		{
			ProcessROT_TRACK(pObj);
		}
	} while (level > 0);
}

void AseLoader::ProcessPOS_TRACK(OUT AseObject *& pObj)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_POS_SAMPLE))
		{
			ASE_POS_SAMPLE sample;
			sample.tick = GetTokenAsInt();
			sample.position.x = GetTokenAsFloat();
			sample.position.z = GetTokenAsFloat();
			sample.position.y = GetTokenAsFloat();

			pObj->m_vecPosTrack.push_back(sample);
		}
	} while (level > 0);
}

void AseLoader::ProcessROT_TRACK(OUT AseObject *& pObj)
{
	int level = 0;
	do
	{
		char* szToken = GetToken();
		if (CompareStr(szToken, "{"))
		{
			level++;
		}
		else if (CompareStr(szToken, "}"))
		{
			level--;
		}
		else if (CompareStr(szToken, ID_ROT_SAMPLE))
		{
			ASE_ROT_SAMPLE sample;

			sample.tick = GetTokenAsInt();

			sample.quaternion.x = GetTokenAsFloat();
			sample.quaternion.z = GetTokenAsFloat();
			sample.quaternion.y = GetTokenAsFloat();
			sample.quaternion.w = GetTokenAsFloat();

			sample.quaternion.x *= sinf(sample.quaternion.w / 2.0f);
			sample.quaternion.z *= sinf(sample.quaternion.w / 2.0f);
			sample.quaternion.y *= sinf(sample.quaternion.w / 2.0f);
			sample.quaternion.w = cosf(sample.quaternion.w / 2.0f);

			if (pObj->m_vecRotTrack.empty() == false)
			{
				sample.quaternion = pObj->m_vecRotTrack.back().quaternion
					* sample.quaternion;
			}

			pObj->m_vecRotTrack.push_back(sample);
		}

	} while (level > 0);
}
