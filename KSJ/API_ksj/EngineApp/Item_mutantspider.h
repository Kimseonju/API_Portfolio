#pragma once
#include "Item.h"

//�뵵 :
//���� : ��Ƽ���ϴ°�
//������ ���� 4���߻��ϰ� ��ġ�� ���ݾ� �ٸ�����
//���⼭�� �������� 2�� �߰� �߻�� ����


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
