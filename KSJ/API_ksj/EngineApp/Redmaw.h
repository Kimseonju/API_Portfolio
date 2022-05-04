#pragma once
#include "Enemy.h"
//�뵵 :
//���� : �÷��̾� �����Ϸ� �ٰ����� ������Ʈ
class EngineCollision;
class Redmaw : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
public: //constructer destructer
	Redmaw();
	~Redmaw();

public:
	Redmaw(const Redmaw& _Other) = delete;
	Redmaw(const Redmaw&& _Other) = delete;

public:
	Redmaw& operator=(const Redmaw& _Other) = delete;
	Redmaw& operator=(const Redmaw&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//������ Find ���°ų� 
	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//�浹

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

