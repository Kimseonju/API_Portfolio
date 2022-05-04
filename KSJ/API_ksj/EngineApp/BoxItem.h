#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include <EngineFSM.h>
#include "CCharacterInfo.h"

//�뵵 :
//���� : �ٴڿ� �������ִ� ������ ��ȣ�ۿ� ���� Ŭ����
//ĳ���� �浹�� �и��� �ϱ�, ��ź�������� �и��� ���⼭ �����ϱ�
//���ڿ� ��Ÿ ������Ʈ�� ó���뵵
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
	LogicValue::ItemBoxType m_ItemType; //������Ÿ��
	CCharacterInfo* m_CharacterInfo;
	bool m_Open;

	//�ʿ� �浹�ߴ��� ���ߴ��� Ȯ��
	Dir m_WallCollision;
	//��� ����� ��ġ�Ǿ��ϴ���
	int m_KeyCount;

	//FSM���� ����� Ÿ�̸�
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

