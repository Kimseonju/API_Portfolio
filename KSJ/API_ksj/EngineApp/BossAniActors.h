#pragma once
#include <EngineActor.h>

//용도 :
//설명 :
class EngineRendererBasic;
class BossAniActors : public EngineActor
{
private: //static
public:  //static func
private:
public: //member
	std::vector< EngineRendererBasic*> m_LeftActor;
	std::vector< EngineRendererBasic*> m_RightActor;
	std::vector<float4> m_LeftStartpos;
	std::vector<float4> m_RightStartpos;
	EngineRendererBasic* PlayerTitle;
	EngineRendererBasic* PlayerBackground;
	EngineRendererBasic* PlayerBody;

	EngineRendererBasic* VS;

	EngineRendererBasic* BossTitle;
	EngineRendererBasic* BossBackground;
	EngineRendererBasic* BossBody;

	EngineRendererBasic* Background;
	float4 m_PlayerTitleStartPos;
	float4 m_BossTitleStartPos;

	int m_MoveCount;
	float m_MoveSpeed;
	bool m_bMove;
	float m_Time;
	float4 m_StartPos;
	float4 m_EndPos;
	float VSAlpha;
	EngineString BossName;
public: //constructer destructer
	BossAniActors();
	~BossAniActors();

public:
	BossAniActors(const BossAniActors& _Other) = delete;
	BossAniActors(const BossAniActors&& _Other) = delete;

public:
	BossAniActors& operator=(const BossAniActors& _Other) = delete;
	BossAniActors& operator=(const BossAniActors&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
public:
	void BossSet(const EngineString& _Boss);
	void VSFadeOut();
	void DeathTask() override;
};
