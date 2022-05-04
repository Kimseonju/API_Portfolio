#pragma once

#include "Item.h"
//�뵵 :
//���� :�ĸ���
//���� �ĸ� �θ����� ĳ���� ������ �ɵ��� �߻�ü ������ (����)

class EngineRendererAnim;
class EngineRendererBasic;
class Item_familiar_brotherbobby : public Item
{
private: //static
public:  //static func
private:
public: //member
	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_familiar_brotherbobby();
	~Item_familiar_brotherbobby();

public:
	Item_familiar_brotherbobby(const Item_familiar_brotherbobby& _Other) = delete;
	Item_familiar_brotherbobby(const Item_familiar_brotherbobby&& _Other) = delete;

public:
	Item_familiar_brotherbobby& operator=(const Item_familiar_brotherbobby& _Other) = delete;
	Item_familiar_brotherbobby& operator=(const Item_familiar_brotherbobby&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
