#pragma once
#include "Enemy.h"
#include <EngineActor.h>


//�������� ���������ʿ��� �߷� ������� ��ȣ�� ������ ��´�.

class EngineCollision;
class EngineRendererAnim;
class EngineRendererBasic;
class Door;
class MOMBoss;

class MomLeg : public Enemy
{
private: //static
public:  //static func
private:
public: //member
	float m_Time;
	//������ ������ ����
	EngineCollision* m_Collision;

	//�׳ɺε�����
	EngineCollision* m_CollisionBody;
	EngineRendererBasic* m_Leg;


	EngineRendererBasic* m_LegHitLayer;

	MOMBoss* m_MOMBoss;
	bool m_Attack;
	bool m_AttackPlay;
	float m_AttackTimer;
	EngineRendererBasic* m_Shadow;

	float m_RenderTimer;
	int m_RenderPattern;
	bool m_RenderUpdateCheck;
	bool m_RenderUpdate;

	int m_AttackSoundCount;
	float4 m_OldPivot;

	//�����ϱ���
	bool m_bAttackSound;
	//������
	bool m_bAttackInSound;
public: //constructer destructer
	MomLeg();
	~MomLeg();

public:
	MomLeg(const MomLeg& _Other) = delete;
	MomLeg(const MomLeg&& _Other) = delete;

public:
	MomLeg& operator=(const MomLeg& _Other) = delete;
	MomLeg& operator=(const MomLeg&& _Other) = delete;

	void Start() override;
	void Update() override;
	void Attack()
	{
		m_Attack = true;
	}
public:
	void MoveRenderUpdate(const float4& num);
	void AllHitRenderOn();
	void AllHitRenderOff();
public:
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

	void BodyStartCol(EngineCollision* _This, EngineCollision* _Other);
	void BodyEndCol(EngineCollision* _This, EngineCollision* _Other);
	void BodyStayCol(EngineCollision* _This, EngineCollision* _Other);
public: //member

	void Init(MOMBoss* _ParentActor);
};

