#include "stdafx.h"
#include "ParticleTest.h"


ParticleTest::ParticleTest()
{
}


ParticleTest::~ParticleTest()
{
	SAFE_RELEASE(m_pVB);
}

void ParticleTest::Init()
{
	//이미지 파일 넣어주어서 쓸것이다.
	m_pTex = g_pTextureManager->GetTexture(string("resources/particle/im.png")/*"resources/particle/sf.jpg"*/);
	if (m_pTex == NULL)
	{
		MessageBox(NULL, TEXT("텍스쳐 없어\n"), 0, 0);
		return;
	}
	size_t numParticle = 5000;
	m_vecAtt.resize(numParticle);
	for (size_t i = 0; i < numParticle; i++)
	{
		Attribute* att = new Attribute();
		att->_position = D3DXVECTOR3(
			GetRandomFloat(-30, 30), 
			GetRandomFloat(-30, 30), 
			GetRandomFloat(-30, 30));
		att->_color = 0xffffffff;//* GetRandomFloat(0, 1);
		m_vecAtt[i] = att;
	}

	g_pDevice->CreateVertexBuffer(numParticle * sizeof(VERTEX_PC),
		D3DUSAGE_POINTS/*포인트전용의 버퍼로 쓰겠다*/
		| D3DUSAGE_DYNAMIC/*값을 계속 바꾸어 줄것인데, dynamic으로 해 놓으면 속도가 빠르다*/
		| D3DUSAGE_WRITEONLY/*쓰기 전용으로*/,
		VERTEX_PC::FVF,
		D3DPOOL_DEFAULT,/*dynamic을 사용할때에는 Managed를 못쓴다. 빨리 값을 바꾸어 주어야 하는데 GPU에서
									  변경을 하는 것이 가장 좋으니, 모두 GPU에 옴긴다*/
		&m_pVB,0);
}

void ParticleTest::Update()
{
	if (GetAsyncKeyState('2') & 0x8000)
	{
		for (size_t i = 0; i < m_vecAtt.size(); i++)
		{
			m_vecAtt[i]->_position.x += GetRandomFloat(-0.001f, 0.01f);
			m_vecAtt[i]->_position.y += GetRandomFloat(0.01f, 0.03f);
			m_vecAtt[i]->_color.a += 0.003f;
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecAtt.size(); i++)
		{
			m_vecAtt[i]->_position.x -= GetRandomFloat(-0.001f, 0.01f);
			m_vecAtt[i]->_position.y -= GetRandomFloat(0.01f, 0.03f);
			m_vecAtt[i]->_color.a -= 0.003f;
		}
	}


	VERTEX_PC* v;
	m_pVB->Lock(0, 0, (LPVOID*)&v, D3DLOCK_DISCARD/*기존에 있었던 값들은 신경쓰지 않는다는 뜻*/);
	for (auto p : m_vecAtt)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;
	}
	m_pVB->Unlock();
}

void ParticleTest::Render()
{
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);// 버퍼를 그릴때 z 값을 넣지 않는다//texture의 외각 부분을 잘라낼 수 있다.
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true); //점의 크기를 조절하겠다.
	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.4f));
	g_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

	g_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);//알파값을 아규멘트1번을 빼와서 쓸것이다.//D3DTOP_SELECTARG1 텍스처의 alpha만 쓸것이다.
	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//D3DTOP_MODULATE 값을 D3DTA_TEXTURE*D3DTA_DIFFUSE 해서 알파값을 쓸것이다. so alpha값을 줄일 수 있다.
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, m_pTex);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_vecAtt.size());

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
