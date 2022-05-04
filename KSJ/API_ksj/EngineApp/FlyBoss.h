#pragma once
#include "Enemy.h"
#include <EngineActor.h>
//�뵵 :
//���� : �ĸ����� �밢������ �����̸� ���� �浹�Ҷ����� �ݴ�������� 90�� ƨ�������´�.
//�߰����� �ĸ���ȯ�Ѵ�.
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
	//��� �����̸鼭 �ĸ���ȯ
	void MoveStart() override;
	void MoveStay() override;
	void AttackStart()override;
	void AttackStay() override;
	void AttackEnd() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;


	//�浹

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
public: //member
};

