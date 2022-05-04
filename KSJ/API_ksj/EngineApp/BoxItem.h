#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include <EngineFSM.h>
#include "CCharacterInfo.h"

//용도 :
//설명 : 바닥에 떨어져있는 아이템 상호작용 전용 클래스
//캐릭터 충돌로 밀리게 하기, 폭탄터질때도 밀리게 여기서 조작하기
//상자와 기타 오브젝트들 처리용도
//
class EngineRendererAnim;
class EngineCollision;
class BoxItem : public EngineActor
{
private: //static
	static LogicValue::ItemBoxType sType;
public:  //static func

	static void TypeNext()
	{
		int temp = static_cast<int>(sType);
		temp++;
		if (temp == static_cast<int>(LogicValue::ItemBoxType::Max))
		{
			temp = 0;
		}
		sType = (LogicValue::ItemBoxType)temp;
	}
private:
	EngineFSM<BoxItem> m_BoxItemFSM;
	EngineRendererAnim* m_RenderBody;
	EngineCollision* m_Collision;
	LogicValue::ItemBoxType m_ItemType; //아이템타입
	CCharacterInfo* m_CharacterInfo;
	bool m_Open;

	//맵에 충돌했는지 안했는지 확인
	Dir m_WallCollision;
	//몇번 열쇠로 터치되야하는지
	int m_KeyCount;

	//FSM에서 사용할 타이머
	float m_FSMTimer;
public: //member

	void SetBoxItemType(LogicValue::ItemBoxType _Type)
	{
		m_ItemType = _Type;
	}
	LogicValue::ItemBoxType GetBoxItemType()
	{
		return m_ItemType;
	}
	void SetKeyCount(int _KeyCount)
	{
		m_KeyCount = _KeyCount;
	}
public: //constructer destructer
	BoxItem();
	~BoxItem();

public:
	BoxItem(const BoxItem& _Other) = delete;
	BoxItem(const BoxItem&& _Other) = delete;

public:
	BoxItem& operator=(const BoxItem& _Other) = delete;
	BoxItem& operator=(const BoxItem&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void UpdateNext() override;
public:

	void SpawnStart();
	void SpawnStay();
	void SpawnEnd();
	void IdleStart();
	void IdleStay();
	void IdleEnd();
	void OpenStart();
	void OpenStay();
	void OpenEnd();

	void MapCollision();
	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

