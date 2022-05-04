#pragma once

#include "Item.h"
//용도 :
//설명 :파리떼
//검은 파리 두마리가 캐릭터 주위를 맴돌며 발사체 막아줌 (쉴드)

class EngineRendererAnim;
class EngineRendererBasic;
class Item_familiar_sackofpennies : public Item
{
private: //static
public:  //static func
private:
public: //member
	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_familiar_sackofpennies();
	~Item_familiar_sackofpennies();

public:
	Item_familiar_sackofpennies(const Item_familiar_sackofpennies& _Other) = delete;
	Item_familiar_sackofpennies(const Item_familiar_sackofpennies&& _Other) = delete;

public:
	Item_familiar_sackofpennies& operator=(const Item_familiar_sackofpennies& _Other) = delete;
	Item_familiar_sackofpennies& operator=(const Item_familiar_sackofpennies&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};

