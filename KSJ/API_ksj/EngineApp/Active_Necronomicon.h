#pragma once
#include "ActiveItem.h"
//용도 :액티브 아이템
//설명 : 현재 방에 있는 모든 적 사망 
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

