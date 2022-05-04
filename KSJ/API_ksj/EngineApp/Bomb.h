#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
class EngineRendererAnim;
class EngineRendererBasic;
class RoomInfo;
//이동시 가속도필요
class Bomb : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineCollision* m_Collision;
    //플레이어와붙고 처음 떨어질때
    EngineCollision* m_CollisionPlayer;

    //폭탄카운트 (맵이동시 카운트초기화)
    float m_Count;
    //폭탄Max카운트
    float m_CountMax;
    int num;
    float m_ChangeCount;
    //폭탄범위
    float m_Range;
    //폭탄 눈물맞을때 속도(임시)
    float m_Speed;

    //플레이어랑 한번 충돌했는지 확인 (놓자마자 충돌방지)
    bool m_bCheckPlayer;
    //이미지
    EngineRendererAnim* m_RenderBody;
    EngineRendererAnim* m_RenderLayer;
    CCharacterInfo* m_CharacterInfo;
    Dir m_WallCollision;

    RoomInfo* m_RoomInfo;
public: // constructer destructer
    Bomb();
    ~Bomb();
public: // delete constructer 
    Bomb(const Bomb& _Other) = delete;
    Bomb(const Bomb&& _Other) = delete;

public: // delete operator
    Bomb& operator=(const Bomb& _Other) = delete;
    Bomb& operator=(const Bomb&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;
    void MapCollider();

public:
    void OffTask() override;
    void StartCol(EngineCollision* _This, EngineCollision* _Other);
    void EndCol(EngineCollision* _This, EngineCollision* _Other);
    void StayCol(EngineCollision* _This, EngineCollision* _Other);
    void PlayerStartCol(EngineCollision* _This, EngineCollision* _Other);
    void PlayerEndCol(EngineCollision* _This, EngineCollision* _Other);
    void PlayerStayCol(EngineCollision* _This, EngineCollision* _Other);

    void SetRoom(RoomInfo* room)
    {
        m_RoomInfo = room;
    }
};
