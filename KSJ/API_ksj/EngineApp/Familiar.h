#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
//�뵵 :
//���� :Item_haloofflies
class EngineRendererAnim;
class Familiar : public EngineActor
{
private: //static
public:  //static func
protected:
	EngineRendererAnim* m_RenderBody;
	EngineActor* m_Target;
	CCharacterInfo* m_CharacterInfo;
public:
	void SetTarget(EngineActor* _Target)
	{
		if (nullptr != m_Target)
		{
			EngineDebug::AssertMsg("if (nullptr != m_Target)");
		}
		m_Target = _Target;
	}

	float m_Angle;
	void ChangeAnimationdir(const EngineString& _dir);
	void FirstAnimationdir(const EngineString& _dir);
	void FirstAnimationclear();
public: //constructer destructer
	Familiar();
	virtual ~Familiar();


public:
	Familiar(const Familiar& _Other) = delete;
	Familiar(const Familiar&& _Other) = delete;

public:
	Familiar& operator=(const Familiar& _Other) = delete;
	Familiar& operator=(const Familiar&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void UpdateNext() override;

	//�йи���鸶�� �ٸ��� �����ϴ°�
	virtual void FamiliarEvent() {};
	//�йи�� �߻��ҋ�
	virtual void FireEvent(const float4& dir) {};
	void AngleCheck(float Angle);
};

