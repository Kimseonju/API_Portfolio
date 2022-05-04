#pragma once
#include "Item.h"

//�뵵 :
//���� : ö�� �ʰ���
//���� �ӵ� 0.7���
//�ʹ��������� 0.1������� ����
class EngineRendererAnim;
class EngineRendererBasic;
class Item_Wirecoathanger : public Item
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_Wirecoathanger();
	~Item_Wirecoathanger();

public:
	Item_Wirecoathanger(const Item_Wirecoathanger& _Other) = delete;
	Item_Wirecoathanger(const Item_Wirecoathanger&& _Other) = delete;

public:
	Item_Wirecoathanger& operator=(const Item_Wirecoathanger& _Other) = delete;
	Item_Wirecoathanger& operator=(const Item_Wirecoathanger&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};