#pragma once
#include "Item.h"
//용도 :
//설명 : 눈물나는양파
//Tears up
//공속 0.7상승
class EngineRendererAnim;
class EngineRendererBasic;
class Item_Active_Necronomicon : public Item
{
private: //static
public:  //static func
private:
public: //member
	//플레이어가 아이템이있었는지 확인하는 변수
	bool m_ItemOn;


	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;
public: //constructer destructer
	Item_Active_Necronomicon();
	~Item_Active_Necronomicon();

public:
	Item_Active_Necronomicon(const Item_Active_Necronomicon& _Other) = delete;
	Item_Active_Necronomicon(const Item_Active_Necronomicon&& _Other) = delete;

public:
	Item_Active_Necronomicon& operator=(const Item_Active_Necronomicon& _Other) = delete;
	Item_Active_Necronomicon& operator=(const Item_Active_Necronomicon&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;

};
