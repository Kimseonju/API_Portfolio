#pragma once
#include "ActiveItem.h"
//�뵵 :��Ƽ�� ������
//���� : ���� �濡 �ִ� ��� �� ��� 
class Active_Kamikaze : public ActiveItem
{
private: //static
public:  //static func
private:
public: //member



public: //constructer destructer
	Active_Kamikaze();
	~Active_Kamikaze();

public:
	Active_Kamikaze(const Active_Kamikaze& _Other) = delete;
	Active_Kamikaze(const Active_Kamikaze&& _Other) = delete;

public:
	Active_Kamikaze& operator=(const Active_Kamikaze& _Other) = delete;
	Active_Kamikaze& operator=(const Active_Kamikaze&& _Other) = delete;

public: //member

	void Start() override;
	void Play() override;
	int ItemType() override;
};

