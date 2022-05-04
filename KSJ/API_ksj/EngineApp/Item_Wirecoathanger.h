#pragma once
#include "Item.h"

//용도 :
//설명 : 철제 옷걸이
//공격 속도 0.7상승
//너무빨라진다 0.1상승으로 변경
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