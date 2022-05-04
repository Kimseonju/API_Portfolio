#pragma once

#include "Item.h"

//�뵵 :
//���� :���ɹ�
//��Ʈ 1�����
class EngineRendererAnim;
class EngineRendererBasic;
class Item_lunch : public Item
{
private: //static
public:  //static func
private:
public: //member

	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;


public: //constructer destructer
	Item_lunch();
	~Item_lunch();

public:
	Item_lunch(const Item_lunch& _Other) = delete;
	Item_lunch(const Item_lunch&& _Other) = delete;

public:
	Item_lunch& operator=(const Item_lunch& _Other) = delete;
	Item_lunch& operator=(const Item_lunch&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};

