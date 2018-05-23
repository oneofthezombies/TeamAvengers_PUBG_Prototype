#pragma once
#include "IDisplayObject.h"
#include "PlayerParts.h"

class PlayerParts;

class PlayerAni : public IDisplayObject
{
private:
    PlayerParts *   m_pRootParts;
    bool			m_isTurnedOnLight;

    D3DXVECTOR3		m_deltaPos;
    D3DXVECTOR3		m_deltaRot;
    D3DXVECTOR3		m_forward;
    D3DXVECTOR3		m_test1;


    bool			m_isMoving;
    float			m_moveSpeed;
    float			m_currMoveSpeedRate;
    float			m_rotationSpeed;

    bool			m_isJumping;
    float			m_jumpPower;
    float			m_gravity;
    float			m_currGravity;

    float			m_maxStepHeight;

    ////추가
    bool            m_isRunnig;
    bool            m_isLive;
    POINT           premousef;

public:
    PlayerAni();
    ~PlayerAni();

    // IDisplayObject을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;

    void UpdatePosition();
    void CreateAllParts();
    void CreateParts(PlayerParts* &pParts, IDisplayObject* pParent,
        D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans,
        vector<vector<int>> &vecUV,  PartTag tag);
    
    //행동별 함수
    void DrawGunInOut();        //총 꺼내고 넣기
    void RunAndWalk();
    void DiedAni();

    PlayerParts* GetChild(int index)
    {
        //return static_cast<PlayerParts*>(m_pRootParts->GetChildRef(index));
        return static_cast<PlayerParts*>(m_pRootParts->GetChildVec()[index]);
    }

    





    vector<vector<int>> uvBody = {
        { 32, 32, 32, 20, 40, 20, 40, 32 },	// 후
    { 20, 32, 20, 20, 28, 20, 28, 32 },	// 전
    { 28, 32, 28, 20, 32, 20, 32, 32 },	// 좌
    { 16, 32, 16, 20, 20, 20, 20, 32 },	// 우
    { 20, 20, 20, 16, 28, 16, 28, 20 },	// 상
    { 28, 16, 28, 20, 36, 20, 36, 16 }	// 하
    };

    vector<vector<int>> uvHead = {
        { 24, 16, 24, 8, 32, 8, 32, 16 },	// 후
    { 8, 16, 8, 8, 16, 8, 16, 16 },		// 전
    { 16, 16, 16, 8, 24, 8, 24, 16 },	// 좌
    { 0, 16, 0, 8, 8, 8, 8, 16 },		// 우
    { 8, 8, 8, 0, 16, 0, 16, 8 },		// 상
    { 16, 0, 16, 8, 24, 8, 24, 0 }		// 하
    };

    vector<vector<int>> uvLArm = {
        { 44, 32, 44, 20, 48, 20, 48, 32 },	// 후
    { 52, 32, 52, 20, 56, 20, 56, 32 },	// 전
    { 40, 32, 40, 20, 44, 20, 44, 32 },	// 좌
    { 48, 32, 48, 20, 52, 20, 52, 32 },	// 우
    { 44, 20, 44, 16, 48, 16, 48, 20 },	// 상
    { 48, 16, 48, 20, 52, 20, 52, 16 }	// 하
    };

    vector<vector<int>> uvRArm = {
        { 48, 32, 48, 20, 44, 20, 44, 32 },	// 후
    { 56, 32, 56, 20, 52, 20, 52, 32 },	// 전
    { 48, 32, 48, 20, 52, 20, 52, 32 },	// 좌
    { 40, 32, 40, 20, 44, 20, 44, 32 },	// 우
    { 48, 20, 48, 16, 44, 16, 44, 20 },	// 상
    { 52, 16, 52, 20, 48, 20, 48, 16 }	// 하
    };

    vector<vector<int>> uvLLeg = {
        { 12, 32, 12, 20, 16, 20, 16, 32 },	// 후
    { 4, 32, 4, 20, 8, 20, 8, 32 },		// 전
    { 8, 32, 8, 20, 12, 20, 12, 32 },	// 좌
    { 0, 32, 0, 20, 4, 20, 4, 32 },		// 우
    { 4, 20, 4, 16, 8, 16, 8, 20 },		// 상
    { 8, 16, 8, 20, 12, 20, 12, 16 }	// 하
    };

    vector<vector<int>> uvRLeg = {
        { 16, 32, 16, 20, 12, 20, 12, 32 },	// 후
    { 8, 32, 8, 20, 4, 20, 4, 32 },		// 전
    { 4, 32, 4, 20, 0, 20, 0, 32 },		// 좌
    { 12, 32, 12, 20, 8, 20, 8, 32 },	// 우
    { 8, 20, 8, 16, 4, 16, 4, 20 },		// 상
    { 12, 16, 12, 20, 8, 20, 8, 16 }	// 하
    };
};

