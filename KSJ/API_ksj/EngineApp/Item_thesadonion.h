#pragma once
#include "Item.h"
//�뵵 :
//���� : �������¾���
//Tears up
//���� 0.7���
//�ʹ��������� 0.1�����Թ߻�� ����
class EngineRendererAnim;
class EngineRendererBasic;
class Item_thesadonion : public Item
{
private: //static
public:  //static func
private:
public: //member



	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;
public: //constructer destructer
	Item_thesadonion();
	~Item_thesadonion();

public:
	Item_thesadonion(const Item_thesadonion& _Other) = delete;
	Item_thesadonion(const Item_thesadonion&& _Other) = delete;

public:
	Item_thesadonion& operator=(const Item_thesadonion& _Other) = delete;
	Item_thesadonion& operator=(const Item_thesadonion&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
