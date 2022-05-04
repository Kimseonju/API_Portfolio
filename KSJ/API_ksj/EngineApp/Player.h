#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
#include <EngineFSM.h>
#include "LogicValue.h"
#include <functional>
// 분류 : 
// 용도 : 
// 설명 : 플레이씬에서 플레이어의 기능을 담당
//우선순위 Die>Damage>attack>Move>Idle
//플레이어 FSM은 나중에
enum class ePlayerState {
    IDLE,
    MOVE,
    ATTACK,
    DAMAGE,
    DIE
};
class EngineRendererAnim;
class EngineRendererBasic;
class Itemaltar;
class ProtectionFly;
class Familiar;
class ActiveItem;
class Player : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    float Speed;
    float4 MovePos;

    EngineRendererAnim* m_RenderHead;
    EngineRendererAnim* m_RenderBody;
    EngineRendererAnim* m_RenderEmotion;

    CCharacterInfo* m_CharacterInfo;

    /////////////안사라지는 오브젝트들!
    //벡터가 적절한데......... 
    std::list<Player_ItemCostume*> ItemCostume;
    //플레이어 주변 눈물 막는 파리
    std::vector<ProtectionFly*> m_ProtectionFly;
    //패밀리어(펫)
    std::vector<Familiar*> m_Familiar;
    ActiveItem* m_ActiveItem;

    /////////////안사라지는 오브젝트들 끝
    float4 m_MapCount;

    //이전 맵 Off처리하기위한 변수
    float4 m_OldMapCount;
    bool m_MapMove; //맵 이동했는지 안했는지
    ePlayerState m_State;
    ePlayerState m_PrevState;

    EngineFSM<Player>m_BodyFSM;
    EngineFSM<Player>m_HeadFSM;
    EngineFSM<Player>m_EmotionFSM;

    //EngineCollision* m_HeadCol; //몬스터와 충돌용
    EngineCollision* m_HeadCol; //충돌
    EngineCollision* m_BodyCol; //벽과충돌
    Dir m_WallLeftRightCollision; //벽충돌한 방향
    Dir m_WallUpDownCollision; //벽충돌한 방향

    Dir m_HeadDir;
    Dir m_PrevHeadDir;
    Dir m_BodyDir;
    Dir m_PrevBodyDir;

    //데미지입었을때 유예기간(데미지 안입는 시간)
    float m_GracePeriod;
    float m_GracePeriodMax;
    //데미지 입을지 안입을지
    bool m_Invincible;
    bool m_DebugInvincible;
    //데미지 입은동안 카운트
    float m_DamageOnOffCount;
    float m_DamageOnOffCountMax;

    //아이템 먹었는지 안먹었는지
    bool m_bCollectionItem;
    //폭탄 놓고 밟은상태면 충돌X
    bool m_bCheckBomb;
    //여기에 함수저장하여 아이템먹은 후 실행시키기
    std::function<void()> m_Itemfunction;
    //입력할지 안할지
    bool m_Input;

    bool m_DamageAni;
    bool m_view;

    bool m_Fly;
    //맵 클리어했는지 확인
    bool m_MapClear;

    int m_MultiShot;
    float m_MultiShotRange;
    bool m_bGuided;
    EngineString strDieActor;
public:
    EngineString& DieActor()
    {
        return strDieActor;
    }

    void SetGuided(bool _Guided)
    {
        m_bGuided = _Guided;
    }
    ActiveItem* GetActiveItem()
    {
        return m_ActiveItem;
    }
    void SetActiveItem(ActiveItem* _ActiveItem)
    {
        m_ActiveItem = _ActiveItem;
    }

    void SetMultiShotPlus(int _Shot)
    {
        m_MultiShot += _Shot;
    }
    bool IsCollectionItem()
    {
        return m_bCollectionItem;
    }
    void SetFly(bool _Fly)
    {
        m_Fly = _Fly;
    }
    void InputOn()
    {
        m_Input = true;
    }
    void InputOff()
    {
        m_Input = false;
    }
    CCharacterInfo* GetCharacterInfo()
    {
        return m_CharacterInfo;
    }

    float4 GetMapCount()
    {
        return m_MapCount;
    }
    float4 GetOldMapCount()
    {
        return m_OldMapCount;
    }
    bool GetMapMove()
    {
        return m_MapMove;
    }
    void SetMapMove(bool _MapMove)
    {
        m_MapMove = _MapMove;
    }
    void SetMapClear(bool _Clear)
    {
        m_MapClear = _Clear;
    }
private://Cam

    bool m_CamMove;
    float m_CamTime;
    float4 m_CamStartPos;
    float4 m_CamEndPos;

public:
    bool IsCamMove() const
    {
        return m_CamMove;
    }
public:
    void CamMoveCheck(const float4& _dir);
    void MapMove();
public: // constructer destructer
    Player();
    ~Player();
public: // delete constructer 
    Player(const Player& _Other) = delete;
    Player(const Player&& _Other) = delete;
    void ItemCostume_Push(Player_ItemCostume* Item)
    {
        ItemCostume.push_back(Item);
    }
public: // delete operator
    Player& operator=(const Player& _Other) = delete;
    Player& operator=(const Player&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void UpdatePrev() override;
    void UpdateNext() override;
    void DebugRender() override;

    void KeyCheck();
    void SetHeadAnimFrameTimer(float _Time);
    void ChangeHeadAnimation(const EngineString& _Str);
    void ChangeBodyAnimation(const EngineString& _Str);

    void ChangeEmotionAnimation(const EngineString& _Str);
    void ChangeFamiliarAnimation(const EngineString& _Str);
    void ProtectionActorSort();
    void ProtectionActorAdd(ProtectionFly* _Actor)
    {
        m_ProtectionFly.push_back(_Actor);
        ProtectionActorSort();
    }


    void FamiliarPush_TargetSetting(Familiar* _Actor);

    void SetItemfunction(class Itemaltar* _Itemaltar, void (Itemaltar::* _Func)())
    {
        m_Itemfunction = std::bind(_Func, _Itemaltar);
    }

    void Die_recovery();
    void SetRenderOrderFly();
public:
    //fsm

    void BodyIDLEStart();
    void BodyIDLEStay();
    void BodyMOVEStart();
    void BodyMOVEStay();

    void HeadIDLEStart();
    void HeadIDLEStay();
    void HeadFIREStart();
    void HeadFIREStay();

    void EmotionIDLEStart();
    void EmotionIDLEStay();

    void EmotionDAMAGEStart();
    void EmotionDAMAGEStay();

    void EmotionItemStart();
    void EmotionItemStay();

    void EmotionDieStart();
    void EmotionDieStay();

public:
    //맵충돌
    void MapCollision();

    //충돌
    void HeadStartCol(EngineCollision* _This, EngineCollision* _Other);
    void HeadEndCol(EngineCollision* _This, EngineCollision* _Other);
    void HeadStayCol(EngineCollision* _This, EngineCollision* _Other);

    void BodyStartCol(EngineCollision* _This, EngineCollision* _Other);
    void BodyEndCol(EngineCollision* _This, EngineCollision* _Other);
    void BodyStayCol(EngineCollision* _This, EngineCollision* _Other);

    void ColDirStop(float Angle);
};