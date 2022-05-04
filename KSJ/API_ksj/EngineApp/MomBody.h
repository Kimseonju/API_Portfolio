#pragma once
#include "Enemy.h"
#include <EngineActor.h>
#include <vector>
#include "LogicValue.h"
//�뵵 :
//���� : �������� �������� �����̰��� ������ �ķ�ģ��.
//�׿ܿ��� ���͸� ��ȯ�ϴµ� ���� ��ȯ�ϴ� �ֱ�� ���������� �����Ѵ�.

class EngineCollision;
class EngineRendererAnim;
class EngineRendererBasic;
class Door;
class MOMBoss;
class MomBody : public Enemy
{
private: //static
	static LogicValue::EnemyType MonsterCount;


public:  //static func
	static void MonsterCountNext();
private:
public: //member
	MOMBoss* m_MOMBoss;
	float m_Time;
	
	int m_Pattern;
	//�����ϴ� ���� ���� �Ʒ��μ�ġ�ǰ� ������ �ݴ��
	float4 m_Dir;

	Door* m_Door;
	EngineRendererBasic* m_Render_MomEye;
	EngineRendererBasic* m_Render_MomBody;
	EngineRendererAnim* m_Render_MomHand;


	EngineRendererBasic* m_Render_MomEyeLayerHit;
	EngineRendererBasic* m_Render_MomBodyLayerHit;
	EngineRendererAnim* m_Render_MomHandLayerHit;

	//�ݸ����� �ϳ��� ����
	//������, ��ġ�� �����ϱ�
	EngineCollision*  m_Collision;
	//�������� ���������Դ��� Ȯ��
	EngineCollision* m_CollisionResearch;

	//������ ����
	float m_EyeTimer;
	bool m_Eye;

	//�հ��� ����
	float m_HandTimer;
	bool m_Hand;


	//������ ����
	float m_BodyTimer;
	bool m_Body;
	bool m_MonsterRecall;

	//���������ִ� ����
	float m_RenderTimer;
	int m_RenderPattern;
public: //constructer destructer
	MomBody();
	~MomBody();

public:
	MomBody(const MomBody& _Other) = delete;
	MomBody(const MomBody&& _Other) = delete;

public:
	MomBody& operator=(const MomBody& _Other) = delete;
	MomBody& operator=(const MomBody&& _Other) = delete;

	void Start() override;
	void Update() override;
	void UpdateNext() override;
	void Die();
	//������������ ����������
	void MoveRender();
	void AllHitRenderOn();
	void AllHitRenderOff();
public:
	void Body()
	{
		if (!m_Body && !m_Eye)
		{
			m_Body = true;
			m_MonsterRecall = true;
		}
	}
	void Eye()
	{
		if (!m_Eye && !m_Body)
		{
			m_Eye = true;
		}
	}

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
	void ResearchStartCol(EngineCollision* _This, EngineCollision* _Other);
	void ResearchEndCol(EngineCollision* _This, EngineCollision* _Other);
	void ResearchStayCol(EngineCollision* _This, EngineCollision* _Other);

public: //member

	void Init(const EngineString& _Dir, const float4& dir, MOMBoss* _ParentActor);
};

