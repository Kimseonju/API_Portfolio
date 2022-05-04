#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �÷��̾� ���Ÿ� ���� �ͷ�
class EngineCollision;
class Turret : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
public: //constructer destructer
	Turret();
	~Turret();

public:
	Turret(const Turret& _Other) = delete;
	Turret(const Turret&& _Other) = delete;

public:
	Turret& operator=(const Turret& _Other) = delete;
	Turret& operator=(const Turret&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//������ Find ���°ų� 
	void FindStay() override;
	void AttackStart()override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//�浹

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

