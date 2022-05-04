#pragma once
#include "Item.h"
//�뵵 :
//���� : �������¾���
//Tears up
//���� 0.7���
class EngineRendererAnim;
class EngineRendererBasic;
class Item_Active_Necronomicon : public Item
{
private: //static
public:  //static func
private:
public: //member
	//�÷��̾ ���������־����� Ȯ���ϴ� ����
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
