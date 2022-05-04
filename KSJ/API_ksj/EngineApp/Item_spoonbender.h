#pragma once
#include "Item.h"

//�뵵 :
//���� : 
//���� �����ǰ����ִ� ������
class EngineRendererAnim;
class EngineRendererBasic;
class Item_spoonbender : public Item
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_spoonbender();
	~Item_spoonbender();

public:
	Item_spoonbender(const Item_spoonbender& _Other) = delete;
	Item_spoonbender(const Item_spoonbender&& _Other) = delete;

public:
	Item_spoonbender& operator=(const Item_spoonbender& _Other) = delete;
	Item_spoonbender& operator=(const Item_spoonbender&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
