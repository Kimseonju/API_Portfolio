#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
// �з� : 
// �뵵 : 
// ���� : �÷��̾����� ������ ��ħ�� ��� Item�� �����������
class EngineRendererBasic;
class Item;
class Itemaltar : public EngineActor
{
private: // Static Var
public: // Static Func
private: // member Var
	Item* m_Item;
	Item* m_TempItem;
	EngineRendererBasic* m_RenderBody;
	EngineCollision* m_Collision;
	bool m_ItemColStart;
public: // constructer destructer
	Itemaltar();
	~Itemaltar();
	

public: // delete constructer 
	Itemaltar(const Itemaltar& _Other) = delete;
	Itemaltar(const Itemaltar&& _Other) = delete;

public: // delete operator
	Itemaltar& operator=(const Itemaltar& _Other) = delete;
	Itemaltar& operator=(const Itemaltar&& _Other) = delete;

public: // member Func
	void Start() override;
	void Update() override;
	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);

	void PlayerFarming();
	void CreateItem();
	Item* CreateItem(LogicValue::ItemGroup _ItemGroup);
	void CreateTempItem(LogicValue::ItemGroup _ItemGroup);
	void SetItemColStart(bool _ItemColStart)
	{
		m_ItemColStart = _ItemColStart;
	}
	void ChangeTempItem_Item();
	//�������� ���� �Լ���
	void ItemOffShop();
	void ItemOnShop();

	void ItemInPlayer();

	void SetItem(Item* _Item)
	{
		m_Item = _Item;
	}
};

