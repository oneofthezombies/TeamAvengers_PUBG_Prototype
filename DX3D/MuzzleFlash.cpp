#include "stdafx.h"
#include "MuzzleFlash.h"

MuzzleFlash::MuzzleFlash()
    : IDisplayObject()
    , m_pTex(nullptr)
    , m_pVB(nullptr)
    , m_isRender(false)
    , m_maxLifeTime(0.4f)
{
}

MuzzleFlash::~MuzzleFlash()
{
    SAFE_RELEASE(m_pTex);
    SAFE_RELEASE(m_pVB);
}

void MuzzleFlash::Init()
{
    m_pTex = g_pTextureManager->GetTexture(TEXT("resources/images/boom_960_720.png"));

    g_pDevice->CreateVertexBuffer(sizeof VERTEX_PC, D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, VERTEX_PC::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);

    VERTEX_PC* v;
    m_pVB->Lock(0, 0, (LPVOID*)&v, D3DLOCK_DISCARD);
    v->p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    v->c = D3DCOLOR_XRGB(255, 255, 255);
    m_pVB->Unlock();
}

void MuzzleFlash::Update()
{
    if (m_isRender)
    {
        const float dt = g_pTimeManager->GetDeltaTime();

        m_lifeTime += dt;
        if (m_lifeTime > m_maxLifeTime)
            m_isRender = false;
    }
}

void MuzzleFlash::Render()
{
    if (!m_isRender) return;

    const auto dv = g_pDevice;
    dv->SetRenderState(D3DRS_ZWRITEENABLE, false);
    dv->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
    dv->SetRenderState(D3DRS_POINTSCALEENABLE, true);
    dv->SetRenderState(D3DRS_LIGHTING, false);

    dv->SetRenderState(D3DRS_POINTSIZE, FtoDw(3.0f));
    dv->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

    dv->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
    dv->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
    dv->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(m_pointScale));

    dv->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    dv->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

    dv->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    dv->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    dv->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    dv->SetTransform(D3DTS_WORLD, &m_matWorld);
    dv->SetTexture(0, m_pTex);
    dv->SetFVF(VERTEX_PC::FVF);
    dv->SetStreamSource(0, m_pVB, 0, sizeof VERTEX_PC);
    dv->DrawPrimitive(D3DPT_POINTLIST, 0, 1);

    dv->SetRenderState(D3DRS_ZWRITEENABLE, true);
    dv->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
    dv->SetRenderState(D3DRS_POINTSCALEENABLE, false);
    dv->SetRenderState(D3DRS_LIGHTING, true);
    dv->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void MuzzleFlash::Flash(const D3DXVECTOR3& pos)
{
    m_pointScale = GetRandomFloat(0.75f, 1.25f);

    D3DXMATRIXA16 r;
    D3DXMatrixRotationZ(&r, GetRandomFloat(0.0f, D3DX_PI * 2.0f));

    D3DXMATRIXA16 t;
    D3DXMatrixTranslation(&t, pos.x, pos.y, pos.z);

    m_matWorld = r * t;

    m_lifeTime = 0.0f;

    m_isRender = true;
}
