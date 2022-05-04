#pragma once
#include "Enemy.h"
//용도 :
//설명 : 플레이어 공격하러 다가가는 파리
class EngineCollision;
class Fly : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;

	//보스를 타겟으로잡고 회전하는용도
	EngineActor* m_Target;
	float m_Angle;
	float m_MoveTime;
	float4 m_Rad;
public: //constructer destructer
	Fly();
	~Fly();

public: 
	Fly(const Fly& _Other) = delete;
	Fly(const Fly&& _Other) = delete;

public:
	Fly& operator=(const Fly& _Other) = delete;
	Fly& operator=(const Fly&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


	void BossTarget(EngineActor* _Target);
	void TargetOut();
public:
	//적상태 Find 상태거나 
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;
public:


	//충돌
	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

