#pragma once
#include <EngineActor.h>
#include "LogicValue.h"
//용도 :
//설명 : 
//
class Itemaltar;
class EngineRendererBasic;
class EngineCollision;
class ShopItem : public EngineActor
{
private: //static
	static LogicValue::ItemGroup Item;



public:  //static func

	static void ItemNext()
	{
		int temp = static_cast<int>(Item);
		temp++;
		if (static_cast<int>(LogicValue::ItemGroup::MAX) == temp)
		{
			temp = 0;
		}
		Item = (LogicValue::ItemGroup)temp;
	}
private:
	EngineRendererBasic* m_RenderBody;
	EngineCollision* m_Collision;
	LogicValue::ItemType m_ItemType; //아이템타입

	//숫자출력
	EngineRendererBasic* m_CoinNumber10;
	EngineRendererBasic* m_CoinNumber1;

	Itemaltar* m_Item;
	//갯수 더할거
	int m_Count;
	 
	int m_Price;

	float m_itemTimer;
	float m_itemTimerMax;
	bool m_Costume;


public: //member



public: //constructer destructer
	ShopItem();
	~ShopItem();

public:
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(const ShopItem&& _Other) = delete;

public:
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(const ShopItem&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void Init(LogicValue::ItemType _ItemType);
	void Init();
	void PlayerFarming();

	void SetCoinImage();
public:

	void StartCol(EngineCollision* _This, EngineCollision* _Other);
	void EndCol(EngineCollision* _This, EngineCollision* _Other);
	void StayCol(EngineCollision* _This, EngineCollision* _Other);
};

