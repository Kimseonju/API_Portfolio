#pragma once

#include "Item.h"
//�뵵 :
//���� :�ĸ���
//���� �ĸ� �θ����� ĳ���� ������ �ɵ��� �߻�ü ������ (����)

class EngineRendererAnim;
class EngineRendererBasic;
class Item_HolyGrail : public Item
{
private: //static
public:  //static func
private:
public: //member
	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_HolyGrail();
	~Item_HolyGrail();

public:
	Item_HolyGrail(const Item_HolyGrail& _Other) = delete;
	Item_HolyGrail(const Item_HolyGrail&& _Other) = delete;

public:
	Item_HolyGrail& operator=(const Item_HolyGrail& _Other) = delete;
	Item_HolyGrail& operator=(const Item_HolyGrail&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};

