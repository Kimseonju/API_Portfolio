#pragma once
#include "Item.h"

//�뵵 :
//���� : ������ ����ƽ
//��Ÿ� 5.25 
//�������� 0.5����
class EngineRendererAnim;
class EngineRendererBasic;
class Item_momslipstick : public Item
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_momslipstick();
	~Item_momslipstick();

public:
	Item_momslipstick(const Item_momslipstick& _Other) = delete;
	Item_momslipstick(const Item_momslipstick&& _Other) = delete;

public:
	Item_momslipstick& operator=(const Item_momslipstick& _Other) = delete;
	Item_momslipstick& operator=(const Item_momslipstick&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
