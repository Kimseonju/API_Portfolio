#pragma once
#include "Item.h"

//용도 :
//설명 : 
//공격력 증가 아이템
class EngineRendererAnim;
class EngineRendererBasic;
class Item_Polyphemus : public Item
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_Polyphemus();
	~Item_Polyphemus();

public:
	Item_Polyphemus(const Item_Polyphemus& _Other) = delete;
	Item_Polyphemus(const Item_Polyphemus&& _Other) = delete;

public:
	Item_Polyphemus& operator=(const Item_Polyphemus& _Other) = delete;
	Item_Polyphemus& operator=(const Item_Polyphemus&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
