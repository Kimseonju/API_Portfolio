#pragma once
#include "Item.h"

//용도 :
//설명 : 멀티샷하는것
//원래는 눈물 4개발사하고 위치가 조금씩 다르지만
//여기서는 눈물갯수 2개 추가 발사로 수정


class EngineRendererAnim;
class EngineRendererBasic;
class Item_mutantspider : public Item
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_mutantspider();
	~Item_mutantspider();

public:
	Item_mutantspider(const Item_mutantspider& _Other) = delete;
	Item_mutantspider(const Item_mutantspider&& _Other) = delete;

public:
	Item_mutantspider& operator=(const Item_mutantspider& _Other) = delete;
	Item_mutantspider& operator=(const Item_mutantspider&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
