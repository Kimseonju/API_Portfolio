#pragma once
#include "Enemy.h"
//용도 :
//설명 : 플레이어보고 일정시간지나면 플레이어공격할때 맞음
class EngineCollision;
class Host : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	bool m_bAttackStart; //공격 시작했을때 데미지를 입는다.

	float m_Timer;
	bool m_bFire;


	bool m_Invincible;
public: //constructer destructer
	Host();
	~Host();

public:
	Host(const Host& _Other) = delete;
	Host(const Host&& _Other) = delete;

public:
	Host& operator=(const Host& _Other) = delete;
	Host& operator=(const Host&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//적상태 Find 상태거나 
	void FindStart() override;
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;
	void AttackStart() override;
	void AttackStay() override;
	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

