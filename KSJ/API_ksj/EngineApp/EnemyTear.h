#pragma once
#include <EngineActor.h>
#include <EngineFSM.h>

//용도 :
//설명 :
class EngineRendererAnim;
class EngineRendererBasic;
class EnemyTear : public EngineActor
{
private: //static
public:  //static func
private: //member
	EngineFSM<EnemyTear>EnemyTearsFsm;

	float4 m_Dir; //방향

	float m_ShotSpeed; //샷속도
	float m_ShotRange; //날아가는 거리
	float m_MoveRange;
	float m_Att; //공격력

	EngineString FireMonster;

	EngineRendererAnim* m_RenderBody;
	EngineRendererBasic* m_Shadow;
	EngineCollision* m_Col;

	float m_GravityForce; //중력
	bool m_Gravity;
	float m_Time;

	//어떤 움직임을 할지
	//0 기본 1 바로떨어짐 2 죽음
	int m_MoveCount;
	//유도탄인지 아닌지
	bool m_bGuided;


	bool m_Drop;
	bool m_SoundMoveEnd;

public:
public: //constructer destructer
	EnemyTear();
	~EnemyTear();

public:
	EnemyTear(const EnemyTear& _Other) = delete;
	EnemyTear(const EnemyTear&& _Other) = delete;

public:
	EnemyTear& operator=(const EnemyTear& _Other) = delete;
	EnemyTear& operator=(const EnemyTear&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void DebugRender() override;
	void PlayFire(EngineActor* _Actor, const float4& _Dir, const float4& _PivotPos,
		const float4& _Pos, const float& _Att, const float& _ShotSpeed, const float& _ShotRange, bool _bGuided=false);
	void MapCollider();

	EngineString& GetFireMonster()
	{
		return FireMonster;
	}
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

