#pragma once
#include "Enemy.h"
#include <EngineActor.h>
//용도 :
//설명 : 파리보스 대각선으로 움직이며 벽에 충돌할때마다 반대방향으로 90도 튕겨져나온다.
//중간마다 파리소환한다.
class EngineCollision;
class EngineRendererAnim;
class Fly;
class FlyBoss : public Enemy
{
private: //static
public:  //static func
private:
public: //member
	float4 m_Dir;
public: //constructer destructer
	FlyBoss();
	~FlyBoss();

	std::list<Fly*> m_AllFly;
public:
	FlyBoss(const FlyBoss& _Other) = delete;
	FlyBoss(const FlyBoss&& _Other) = delete;

public:
	FlyBoss& operator=(const FlyBoss& _Other) = delete;
	FlyBoss& operator=(const FlyBoss&& _Other) = delete;

	void Start() override;
	void Update() override;
	void DebugRender() override;

public:
	void MapCollider() override;

public:
	//계속 움직이면서 파리소환
	void MoveStart() override;
	void MoveStay() override;
	void AttackStart()override;
	void AttackStay() override;
	void AttackEnd() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;


	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
public: //member
};

