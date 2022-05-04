#pragma once
#include "ActiveItem.h"
//�뵵 :��Ƽ�� ������
//���� : ���� �濡 �ִ� ��� �� ��� 
class Active_Necronomicon : public ActiveItem
{
private: //static
public:  //static func
private: 
public: //member



public: //constructer destructer
	Active_Necronomicon();
	~Active_Necronomicon();

public: 
	Active_Necronomicon(const Active_Necronomicon& _Other) = delete;
	Active_Necronomicon(const Active_Necronomicon&& _Other) = delete;

public:
	Active_Necronomicon& operator=(const Active_Necronomicon& _Other) = delete;
	Active_Necronomicon& operator=(const Active_Necronomicon&& _Other) = delete;

public: //member

	void Start() override;
	void Play() override;
	int ItemType() override;
};

