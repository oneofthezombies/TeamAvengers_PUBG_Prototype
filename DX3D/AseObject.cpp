#include "stdafx.h"
#include "AseObject.h"


AseObject::AseObject()
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


AseObject::~AseObject()
{
}

void AseObject::Init()
{
	SetupTexture();
	CalcLocalTM();
}

void AseObject::Update(int tickCount, D3DXMATRIXA16 * pMatParent)
{
	D3DXMATRIXA16 matLocalT, matLocalR;

	CalcLocalTranslationMatrix(tickCount, matLocalT);
	CalcLocalRotationMatrix(tickCount, matLocalR);

	m_matLocalTM = matLocalR * matLocalT;

	m_matWorldTM = m_matLocalTM;

	if (pMatParent != NULL)
		m_matWorldTM *= *pMatParent;

	for (auto p : m_vecChild)
	{
		p->Update(tickCount, &m_matWorldTM);
	}
}

void AseObject::Render()
{
	//D3DXMatrixIdentity(&m_matWorldTM);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pDevice->SetTexture(0, m_pTex);
	g_pDevice->SetMaterial(&m_mtl);
	g_pDevice->SetFVF(VERTEX_PNT::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
		&m_vecVertex[0], sizeof(VERTEX_PNT));

	for (auto p : m_vecChild)
	{
		p->Render();
	}
}

void AseObject::AddChild(AseObject * pChild)
{
	if (pChild == NULL) return;
	m_vecChild.push_back(pChild);
}

void AseObject::ReleaseAll()
{
	for (auto p : m_vecChild)
	{
		p->ReleaseAll();
	}
	Release();
}

void AseObject::SetupTexture()
{
	m_pTex = g_pTextureManager->GetTexture(m_texName);
	
	for (auto p : m_vecChild)
	{
		p->SetupTexture();
	}
}

void AseObject::CalcLocalTM(AseObject * pParent)
{
	m_matLocalTM = m_matWorldTM;

	if (pParent != NULL)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, 0, &pParent->m_matWorldTM);
		m_matLocalTM *= matInvParent;
	}

	for (auto p : m_vecChild)
	{
		p->CalcLocalTM(this);
	}
}

void AseObject::CalcLocalTranslationMatrix(IN int tickCount, OUT D3DXMATRIXA16 & mat)
{
	D3DXMatrixIdentity(&mat);

	if (m_vecPosTrack.empty() == true)
	{
		mat._41 = m_matLocalTM._41;
		mat._42 = m_matLocalTM._42;
		mat._43 = m_matLocalTM._43;
	}
	else if (tickCount <= m_vecPosTrack.front().tick)
	{
		mat._41 = m_vecPosTrack.front().position.x;
		mat._42 = m_vecPosTrack.front().position.y;
		mat._43 = m_vecPosTrack.front().position.z;
	}
	else if (tickCount >= m_vecPosTrack.back().tick)
	{
		mat._41 = m_vecPosTrack.back().position.x;
		mat._42 = m_vecPosTrack.back().position.y;
		mat._43 = m_vecPosTrack.back().position.z;
	}
	else
	{
		int nNext = -1;
		for (size_t i = 0; i < m_vecPosTrack.size(); i++)
		{
			if (m_vecPosTrack[i].tick > tickCount)
			{
				nNext = i;
				break;
			}
		}
		int nPrev = nNext - 1;
		
		float t = (tickCount - m_vecPosTrack[nPrev].tick) /
			(float)(m_vecPosTrack[nNext].tick - m_vecPosTrack[nPrev].tick);
		
		D3DXVECTOR3 v;
		D3DXVec3Lerp(&v, 
			&m_vecPosTrack[nPrev].position,
			&m_vecPosTrack[nNext].position, t);
		mat._41 = v.x;
		mat._42 = v.y;
		mat._43 = v.z;
	}
}

void AseObject::CalcLocalRotationMatrix(IN int tickCount, OUT D3DXMATRIXA16 & mat)
{
	D3DXMatrixIdentity(&mat);

	if (m_vecRotTrack.empty() == true)
	{
		mat = m_matLocalTM;
		mat._41 = 0.0f;
		mat._42 = 0.0f;
		mat._43 = 0.0f;
	}
	else if (tickCount <= m_vecRotTrack.front().tick)
	{
		D3DXMatrixRotationQuaternion(&mat, 
			&m_vecRotTrack.front().quaternion);
	}
	else if (tickCount >= m_vecRotTrack.back().tick)
	{
		D3DXMatrixRotationQuaternion(&mat,
			&m_vecRotTrack.back().quaternion);
	}
	else
	{
		int nNext = -1;
		for (size_t i = 0; i < m_vecRotTrack.size(); i++)
		{
			if (m_vecRotTrack[i].tick > tickCount)
			{
				nNext = i;
				break;
			}
		}
		int nPrev = nNext - 1;

		float t = (tickCount - m_vecRotTrack[nPrev].tick) /
			(float)(m_vecRotTrack[nNext].tick - m_vecRotTrack[nPrev].tick);

		D3DXQUATERNION q;
		D3DXQuaternionSlerp(&q,
			&m_vecRotTrack[nPrev].quaternion,
			&m_vecRotTrack[nNext].quaternion, t);
		D3DXMatrixRotationQuaternion(&mat, &q);
	}
}
