#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �÷��̾� �����Ϸ� �ٰ����� �ĸ�
class EngineCollision;
class Horf : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
public: //constructer destructer
	Horf();
	~Horf();

public:
	Horf(const Horf& _Other) = delete;
	Horf(const Horf&& _Other) = delete;

public:
	Horf& operator=(const Horf& _Other) = delete;
	Horf& operator=(const Horf&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//������ Find ���°ų� 
	void FindStay() override;
	void AttackStart() override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//�浹

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

