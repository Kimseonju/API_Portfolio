#pragma once
#include "Enemy.h"
//용도 :
//설명 : 원거리 공격하는 파리
//플레이어가 시야안에왔을때만 공격만함
class EngineRendererAnim;
class Pooter : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_MoveTime;
	float4 m_Rad;
public: //constructer destructer
	Pooter();
	~Pooter();

public: 
	Pooter(const Pooter& _Other) = delete;
	Pooter(const Pooter&& _Other) = delete;

public:
	Pooter& operator=(const Pooter& _Other) = delete;
	Pooter& operator=(const Pooter&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void DebugRender() override;

public:
	//적상태 Find 상태거나 
	void FindStay() override;
	void AttackStart() override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;


	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

