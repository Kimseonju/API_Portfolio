#pragma once
#include <EngineActor.h>
#include <EngineFSM.h>

//용도 :
//설명 :
class EngineRendererAnim;
class EngineRendererBasic;
class RoomInfo;
class Enemy;
class Tears : public EngineActor
{
private: //static
public:  //static func
private: //member

	EngineFSM<Tears>TearsFsm;
	Enemy* m_Target;

	float4 m_Dir; //방향

	float m_ShotSpeed; //샷속도
	float m_ShotRange; //날아가는 거리
	float m_MoveRange;
	float m_Att; //공격력

	float4 m_CheckPos;
	EngineRendererAnim* m_RenderBody;
	EngineRendererBasic* m_Shadow;
	EngineCollision* m_Col;

	float m_GravityForce; //중력
	bool m_Gravity;
	float m_Time;

	bool m_FSMDie;
	//어떤 움직임을 할지
	//0 기본 1 바로떨어짐 2 죽음
	int m_MoveCount;

	bool m_bGuided;
	bool m_Drop;
	bool m_SoundMoveEnd;
	float4 m_Movepos;
	RoomInfo* m_Room;
public:
	void SetRoom(RoomInfo* _Room)
	{
		m_Room = _Room;
	}
public: //constructer destructer
	Tears();
	~Tears();

public:
	Tears(const Tears& _Other) = delete;
	Tears(const Tears&& _Other) = delete;

public:
	Tears& operator=(const Tears& _Other) = delete;
	Tears& operator=(const Tears&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void UpdateNext() override;
	void DebugRender() override;
	void PlayFire(EngineActor* _Actor, const float4& _Dir, const float4& _PivotPos,
		const float4& _Pos, const float& _Att, const float& _ShotSpeed, const float& _ShotRange, bool _bGuided = false);
	void MapCollider();

public:
	//fsm
	void MoveStay();
	void MoveEnd();
public:
	//충돌
	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

