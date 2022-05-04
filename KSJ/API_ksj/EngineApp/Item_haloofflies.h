#pragma once

#include "Item.h"
//�뵵 :
//���� :�ĸ���
//���� �ĸ� �θ����� ĳ���� ������ �ɵ��� �߻�ü ������ (����)

class EngineRendererAnim;
class EngineRendererBasic;
class Item_haloofflies : public Item
{
private: //static
public:  //static func
private: 
public: //member
	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_haloofflies();
	~Item_haloofflies();

public: 
	Item_haloofflies(const Item_haloofflies& _Other) = delete;
	Item_haloofflies(const Item_haloofflies&& _Other) = delete;

public:
	Item_haloofflies& operator=(const Item_haloofflies& _Other) = delete;
	Item_haloofflies& operator=(const Item_haloofflies&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};

