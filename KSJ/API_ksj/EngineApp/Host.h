#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �÷��̾�� �����ð������� �÷��̾�����Ҷ� ����
class EngineCollision;
class Host : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	bool m_bAttackStart; //���� ���������� �������� �Դ´�.

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

