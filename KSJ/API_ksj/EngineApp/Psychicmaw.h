#pragma once
#include "Enemy.h"
//용도 :
//설명 : 유도탄 발사하는 몬스터
//이미지수정중
class EngineCollision;
class EngineRendererAnim;
class Psychicmaw : public Enemy
{
private: // Static Var
public: // Static Func
private: // member Var

	EngineCollision* m_Collision;
	EngineRendererAnim* m_RenderEffect;
public: //constructer destructer
	Psychicmaw();
	~Psychicmaw();

public:
	Psychicmaw(const Psychicmaw& _Other) = delete;
	Psychicmaw(const Psychicmaw&& _Other) = delete;

public:
	Psychicmaw& operator=(const Psychicmaw& _Other) = delete;
	Psychicmaw& operator=(const Psychicmaw&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;


public:
	//적상태 Find 상태거나 
	void FindStay() override;
	void AttackStart() override;
	void AttackStay() override;
	void DieStart()override;
	void DieStay() override;
	void DieEnd() override;

	//충돌

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

