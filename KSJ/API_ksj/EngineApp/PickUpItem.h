#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include "CCharacterInfo.h"

//용도 :
//설명 : 바닥에 떨어져있는 아이템 상호작용 전용 클래스
//캐릭터 충돌로 밀리게 하기, 폭탄터질때도 밀리게 여기서 조작하기
//상자와 기타 오브젝트들 처리용도
//
class EngineRendererAnim;
class EngineCollision;
class PickUpItem : public EngineActor
{
private: //static
	static bool Heart;
	static LogicValue::ItemType sType;
	//false 는 0 하트 반개
	//false 는 1 하트 한개
public:  //static func

	static void TypeNext()
	{
		int temp = static_cast<int>(sType);
		temp++;
		if (temp == static_cast<int>(LogicValue::ItemType::Max))
		{
			temp = 0;
		}
		sType = (LogicValue::ItemType)temp;
	}

	static void HeartNext()
	{
		Heart = !Heart;
	}
private:
	EngineRendererAnim* m_RenderBody;
	EngineCollision* m_Collision;
	LogicValue::ItemType m_ItemType; //아이템타입
	CCharacterInfo* m_CharacterInfo;
	float m_Time;
	bool m_Idle;
	//충돌했는지 안했는지 (플레이어랑)
	bool m_bCollision;
	bool m_PickSound;
	//맵에 충돌했는지 안했는지 확인
	Dir m_WallCollision;
	//갯수 더할거
	int m_Count;
public: //member

	void SetPickUpItemType(LogicValue::ItemType _Type)
	{
		m_ItemType = _Type;
	}
	LogicValue::ItemType GetPickUpItemType()
	{
		return m_ItemType;
	}
	void SetCount(int _Count)
	{
		m_Count = _Count;
	}
	int GetCount() const
	{
		return m_Count;
	}
public: //constructer destructer
	PickUpItem();
	~PickUpItem();

public: 
	PickUpItem(const PickUpItem& _Other) = delete;
	PickUpItem(const PickUpItem&& _Other) = delete;

public:
	PickUpItem& operator=(const PickUpItem& _Other) = delete;
	PickUpItem& operator=(const PickUpItem&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void UpdateNext() override;
public:

	void Init(LogicValue::ItemType _ItemType);
	void Init();
	void Create();
	void MapCollision();
	
	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

