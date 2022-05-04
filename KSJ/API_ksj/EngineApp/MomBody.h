#pragma once
#include "Enemy.h"
#include <EngineActor.h>
#include <vector>
#include "LogicValue.h"
//용도 :
//설명 : 아이작이 범위내에 가까이가면 손으로 후려친다.
//그외에는 몬스터를 소환하는데 몬스터 소환하는 주기는 맘보스에서 관리한다.

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
	//공격하는 방향 문이 아래로설치되고 방향을 반대로
	float4 m_Dir;

	Door* m_Door;
	EngineRendererBasic* m_Render_MomEye;
	EngineRendererBasic* m_Render_MomBody;
	EngineRendererAnim* m_Render_MomHand;


	EngineRendererBasic* m_Render_MomEyeLayerHit;
	EngineRendererBasic* m_Render_MomBodyLayerHit;
	EngineRendererAnim* m_Render_MomHandLayerHit;

	//콜리전은 하나로 통일
	//사이즈, 위치만 변경하기
	EngineCollision*  m_Collision;
	//아이작이 범위내에왔는지 확인
	EngineCollision* m_CollisionResearch;

	//눈관련 변수
	float m_EyeTimer;
	bool m_Eye;

	//손관련 변수
	float m_HandTimer;
	bool m_Hand;


	//몸관련 변수
	float m_BodyTimer;
	bool m_Body;
	bool m_MonsterRecall;

	//동적느낌주는 변수
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
	//동적느낌나는 랜더러생성
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


	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
	void ResearchStartCol(EngineCollision* _This, EngineCollision* _Other);
	void ResearchEndCol(EngineCollision* _This, EngineCollision* _Other);
	void ResearchStayCol(EngineCollision* _This, EngineCollision* _Other);

public: //member

	void Init(const EngineString& _Dir, const float4& dir, MOMBoss* _ParentActor);
};

