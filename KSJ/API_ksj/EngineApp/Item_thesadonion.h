#pragma once
#include "Item.h"
//용도 :
//설명 : 눈물나는양파
//Tears up
//공속 0.7상승
//너무빨라진다 0.1빠르게발사로 수정
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
