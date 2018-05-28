#include "stdafx.h"
#include "AllocateHierarchy.h"


// 프레임 생성 : 새로 메모리를 할당해서 프레임을 생성하고 ppNewFrame 인자에 연결
// 생성한 프레임의 이름은 모델링 프로그램에서 정해준 프레임의 이름을 인자로 받아 지정
// 프레임 전체를 트리구조로 꾸미기 위한 준비 작업
STDMETHODIMP AllocateHierarchy::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	FRAME_EX* pFrameEx = new FRAME_EX;
	
	// TODO : 이름을 잘 저장해주세요. 물론 해제도.
	if (Name != NULL)
	{
		pFrameEx->Name = new char[strlen(Name) + 1];
		strcpy_s(pFrameEx->Name, (strlen(Name) + 1), Name);
	}
	else
	{
		pFrameEx->Name = NULL;
	}

	D3DXMatrixIdentity(&pFrameEx->TransformationMatrix);
	D3DXMatrixIdentity(&pFrameEx->CombinedTM);

	pFrameEx->pMeshContainer = NULL;
	pFrameEx->pFrameFirstChild = NULL;
	pFrameEx->pFrameSibling = NULL;

	*ppNewFrame = pFrameEx;
	
	

	return S_OK;
}


// 매쉬 컨테이너 생성 : 새로 메모리를 할당해서프레임을 생성하고 ppNewMeshContainer 인자에 연결
// 매쉬의 이름, 머티리얼, 텍스처를 지정
// 생성한 매쉬 컨테이너에 pSkinInfo 를 연결
// Skinning 을 위한 준비 작업
STDMETHODIMP AllocateHierarchy::CreateMeshContainer(
	THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	MESHCONTAINER_EX* pMeshContainerEx = NULL;
	LPD3DXMESH pMesh = NULL;

	if (pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		assert(false && _T("D3DXMESHTYPE_MESH 타입만 사용 가능"));
	}

	pMesh = pMeshData->pMesh;

	if (pMesh->GetFVF() == 0)
	{
		assert(false && _T("FVF Flag 가 지정되지 않음"));
	}

	pMeshContainerEx = new MESHCONTAINER_EX;
	memset(pMeshContainerEx, 0, sizeof(MESHCONTAINER_EX));
	
	if (Name != NULL)
	{
		pMeshContainerEx->Name = new char[strlen(Name) + 1];
		strcpy_s(pMeshContainerEx->Name, (strlen(Name) + 1), Name);
	}
	
	// if no normals are in the mesh, add them
	if ((pMesh->GetFVF() & D3DFVF_NORMAL) == false)
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL, g_pDevice, &pMesh);

		D3DXComputeNormals(pMesh, NULL);
	}

	pMesh->AddRef();
	pMeshContainerEx->pOrigMesh = pMesh;
	pMeshContainerEx->pOrigMesh->CloneMeshFVF(
		pMeshContainerEx->pOrigMesh->GetOptions(),
		pMeshContainerEx->pOrigMesh->GetFVF(),
		g_pDevice,
		&pMeshContainerEx->pWorkMesh);

	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		MTLTEX* pMtlTex = new MTLTEX;
		pMtlTex->SetMaterial(pMaterials[i].MatD3D);
		pMtlTex->SetTexture(g_pTextureManager->GetTexture(m_path + pMaterials[i].pTextureFilename));
		pMeshContainerEx->vecMtlTex.push_back(pMtlTex);
	}

	// pSkinInfo 의 데이터 저장
	if (pSkinInfo != NULL)
	{
		pMeshContainerEx->pSkinInfo = pSkinInfo;
		(pSkinInfo)->AddRef();

		// pSkinInfo->GetNumBones() : 이 매쉬에 영향을 주는 본(프레임)의 갯수
		DWORD numBones = pSkinInfo->GetNumBones();
		pMeshContainerEx->ppBoneMatrixPtrs = new D3DXMATRIX*[numBones];
		pMeshContainerEx->pBoneOffsetMatrices = new D3DXMATRIX[numBones];
		pMeshContainerEx->pFinalBoneMatrices = new D3DXMATRIX[numBones];

		for (DWORD i = 0; i < numBones; ++i)
		{
			pMeshContainerEx->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
		}
	}

	*ppNewMeshContainer = pMeshContainerEx;
	
	return S_OK;
}


//생성했던 프레임을 해제
//생성시 동적 할당 해줬던 부분을 모두 해제
STDMETHODIMP AllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);

	return S_OK;
}


//생성했던 매쉬 컨테이너를 해제
//생성시 동적 할당 해줬던 부분을 모두 해제
STDMETHODIMP AllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	MESHCONTAINER_EX* pMeshContainerEx = (MESHCONTAINER_EX*)pMeshContainerToFree;
	if (pMeshContainerEx == NULL)
		return E_FAIL;

	SAFE_DELETE_ARRAY(pMeshContainerEx->Name);
	SAFE_RELEASE(pMeshContainerEx->pOrigMesh);
	SAFE_RELEASE(pMeshContainerEx->pWorkMesh);

	for (auto p : pMeshContainerEx->vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	SAFE_DELETE_ARRAY(pMeshContainerEx->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pMeshContainerEx->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pMeshContainerEx->pFinalBoneMatrices);

	SAFE_RELEASE(pMeshContainerEx->pSkinInfo);

	return S_OK;
}