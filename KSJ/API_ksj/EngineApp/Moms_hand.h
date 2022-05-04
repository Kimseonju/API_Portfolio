#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �÷��̾���ġ���ִٰ� �����ð��������� ���߰� ������ ������Ʈ
class EngineCollision;
class EngineRendererBasic;
class Moms_hand : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	float m_Time;
	EngineRendererBasic* m_Shadow;

public: //constructer destructer
	Moms_hand();
	~Moms_hand();

public:
	Moms_hand(const Moms_hand& _Other) = delete;
	Moms_hand(const Moms_hand&& _Other) = delete;

public:
	Moms_hand& operator=(const Moms_hand& _Other) = delete;
	Moms_hand& operator=(const Moms_hand&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//������ Find ���°ų� 
	void FindStart() override;
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;
	void AttackStart() override;
	void AttackStay() override;

	//�浹

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

