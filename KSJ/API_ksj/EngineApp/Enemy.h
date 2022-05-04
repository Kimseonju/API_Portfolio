#pragma once
#include <EngineActor.h>
#include <EngineFSM.h>
#include "CCharacterInfo.h"

class EngineRendererAnim;
class RoomInfo;
class Enemy : public EngineActor
{

private: // Static Var
public: // Static Func
protected: // member Var
    EngineFSM<Enemy> m_MonsterFSM;
    EngineRendererAnim* m_RenderBody;
    CCharacterInfo* m_CharacterInfo;
    float4 m_MapCount;

    //
    bool m_FSMDie;
    bool m_CheckDie;
    //맵에 충돌했는지 안했는지 확인
    Dir m_WallCollision;
    RoomInfo* m_RoomInfo;

    EngineRendererAnim* m_RenderHitLayer;
    float m_Time;
public:

    EngineRendererAnim* GetRenderBody()
    {
        return m_RenderBody;
    }

    void SetRenderBody(EngineRendererAnim* _RenderBody)
    {
        m_RenderBody = _RenderBody;
    }
    EngineFSM<Enemy>* GetMonsterFSM()
    {
        return &m_MonsterFSM;
    }
    CCharacterInfo* GetCharacterInfo()
    {
        return m_CharacterInfo;
    }

    void SetMapPos(int _X, int _Y)
    {
        float4 pos = float4::ZERO;
        pos.x = _X * 960.f;
        pos.y = _Y * 540.f;
        SetPosition(pos);
    }
    void ColDirStop(float Angle);
public: // constructer destructer
    Enemy();
    virtual ~Enemy();
public:
public: // delete constructer 
    Enemy(const Enemy& _Other) = delete;
    Enemy(const Enemy&& _Other) = delete;
public: // delete operator
    Enemy& operator=(const Enemy& _Other) = delete;
    Enemy& operator=(const Enemy&& _Other) = delete;

public: // member Func
    virtual void Start() override;
    virtual void Update() override;
    virtual void UpdateNext() override;
    virtual void UpdatePrev() override;
    virtual void DebugRender() override;

    void OnTask() override { EngineActor::OnTask(); };

public:
    //적상태 Find 상태거나 
    virtual void FindStart() {}
    virtual void FindStay() {}
    virtual void FindEnd() {}
    virtual void MoveStart() {}
    virtual void MoveStay() {}
    virtual void MoveEnd() {}
    virtual void AttackStart() {}
    virtual void AttackStay() {}
    virtual void AttackEnd() {}
    virtual void DieStart();
    virtual void DieStay();
    virtual void DieEnd() {}

    //죽는 상태로 바꿔야될떄 사용 
    //ex) Deathshead
    void FSMDiePlay();
    virtual void MapCollider();

    void SetRoomInfo(RoomInfo* _Info)
    {
        m_RoomInfo = _Info;
    }
    RoomInfo* GetRoomInfo()
    {
        return m_RoomInfo;
    }
};