#pragma once
#include "IDisplayObject.h"

//불값으로 해도됨.
enum PartTag
{
    tEmpty = 1,
    tGun
};

class PlayerParts :
    public IDisplayObject
{
private:
    vector<VERTEX_PC>	m_vecPCVertex;
    vector<VERTEX_PT>	m_vecPTVertex;

    bool				m_isMoving;
    float				m_rotXAngle;
    float				m_rotXSpeed;
    PartTag             m_ePartTag;

    LPDIRECT3DTEXTURE9	m_tex;

public:
    PlayerParts(float rotXSpeed = 0.0f);
    ~PlayerParts();

    // IDisplayObject을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    void Init(D3DXMATRIX* pMat, vector<vector<int>> &vecUV);
    void SetPCVertex(vector<VERTEX_PC> &vecOut,
        vector<D3DXVECTOR3> &vecVertex);
    void SetPTVertex(vector<VERTEX_PT> &vecOut,
        vector<D3DXVECTOR3> &vecVertex, vector<vector<int>> &uv);
    void SetMovingState(bool isMoving);
    void MakeUVList(vector<D3DXVECTOR2> &out,
        vector<vector<int>> &uv);
    //////////추가한부분
    void SetPartTag(PartTag a);
    PartTag GetPartTag();
    void SetRotXspeed(float a);
    float GetRotXspeed();       //오른팔 왼팔의 반대방향 세팅
    void SyncMotion();          //뛰다가 총 집어넣었을때 왼팔과 오른팔 각을 맞추기 위해.
};



