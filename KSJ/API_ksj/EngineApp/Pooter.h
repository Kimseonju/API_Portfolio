#pragma once
#include "Enemy.h"
//�뵵 :
//���� : ���Ÿ� �����ϴ� �ĸ�
//�÷��̾ �þ߾ȿ��������� ���ݸ���
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

