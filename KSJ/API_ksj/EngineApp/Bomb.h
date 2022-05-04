#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
class EngineRendererAnim;
class EngineRendererBasic;
class RoomInfo;
//�̵��� ���ӵ��ʿ�
class Bomb : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
    EngineCollision* m_Collision;
    //�÷��̾�ͺٰ� ó�� ��������
    EngineCollision* m_CollisionPlayer;

    //��źī��Ʈ (���̵��� ī��Ʈ�ʱ�ȭ)
    float m_Count;
    //��źMaxī��Ʈ
    float m_CountMax;
    int num;
    float m_ChangeCount;
    //��ź����
    float m_Range;
    //��ź ���������� �ӵ�(�ӽ�)
    float m_Speed;

    //�÷��̾�� �ѹ� �浹�ߴ��� Ȯ�� (���ڸ��� �浹����)
    bool m_bCheckPlayer;
    //�̹���
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
