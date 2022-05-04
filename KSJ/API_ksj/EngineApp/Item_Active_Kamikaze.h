#pragma once
#include "Item.h"
//�뵵 :
//���� : �������¾���
//Tears up
//���� 0.7���
class EngineRendererAnim;
class EngineRendererBasic;
class Item_Active_Kamikaze : public Item
{
private: //static
public:  //static func
private:
public: //member
	bool m_ItemOn;



	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;
public: //constructer destructer
	Item_Active_Kamikaze();
	~Item_Active_Kamikaze();

public:
	Item_Active_Kamikaze(const Item_Active_Kamikaze& _Other) = delete;
	Item_Active_Kamikaze(const Item_Active_Kamikaze&& _Other) = delete;

public:
	Item_Active_Kamikaze& operator=(const Item_Active_Kamikaze& _Other) = delete;
	Item_Active_Kamikaze& operator=(const Item_Active_Kamikaze&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
