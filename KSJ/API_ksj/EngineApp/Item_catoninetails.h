#pragma once
#include "Item.h"

//�뵵 :
//���� : 
//���� �ӵ� �������� �ϴ� ������



class EngineRendererAnim;
class EngineRendererBasic;
class Item_catoninetails : public Item
{
private: //static
public:  //static func
private:
public: //member


	EngineRendererAnim* m_Anim;
	EngineRendererBasic* m_Basic;

public: //constructer destructer
	Item_catoninetails();
	~Item_catoninetails();

public:
	Item_catoninetails(const Item_catoninetails& _Other) = delete;
	Item_catoninetails(const Item_catoninetails&& _Other) = delete;

public:
	Item_catoninetails& operator=(const Item_catoninetails& _Other) = delete;
	Item_catoninetails& operator=(const Item_catoninetails&& _Other) = delete;

public: //member
	void Start() override;
	void PlayerFarming() override;
	EngineRendererBasic* PlayerRenderItem() override;
};
