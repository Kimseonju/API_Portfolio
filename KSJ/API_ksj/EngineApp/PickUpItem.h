#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
#include "CCharacterInfo.h"

//�뵵 :
//���� : �ٴڿ� �������ִ� ������ ��ȣ�ۿ� ���� Ŭ����
//ĳ���� �浹�� �и��� �ϱ�, ��ź�������� �и��� ���⼭ �����ϱ�
//���ڿ� ��Ÿ ������Ʈ�� ó���뵵
//
class EngineRendererAnim;
class EngineCollision;
class PickUpItem : public EngineActor
{
private: //static
	static bool Heart;
	static LogicValue::ItemType sType;
	//false �� 0 ��Ʈ �ݰ�
	//false �� 1 ��Ʈ �Ѱ�
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
	LogicValue::ItemType m_ItemType; //������Ÿ��
	CCharacterInfo* m_CharacterInfo;
	float m_Time;
	bool m_Idle;
	//�浹�ߴ��� ���ߴ��� (�÷��̾��)
	bool m_bCollision;
	bool m_PickSound;
	//�ʿ� �浹�ߴ��� ���ߴ��� Ȯ��
	Dir m_WallCollision;
	//���� ���Ұ�
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

