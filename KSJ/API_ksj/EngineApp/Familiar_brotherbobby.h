#pragma once
#include "Familiar.h"
//용도 :
//설명 :
class Familiar_brotherbobby : public Familiar
{
private: //static
public:  //static func
private: 
public: //member



public: //constructer destructer
	Familiar_brotherbobby();
	~Familiar_brotherbobby();

public: 
	Familiar_brotherbobby(const Familiar_brotherbobby& _Other) = delete;
	Familiar_brotherbobby(const Familiar_brotherbobby&& _Other) = delete;

public:
	Familiar_brotherbobby& operator=(const Familiar_brotherbobby& _Other) = delete;
	Familiar_brotherbobby& operator=(const Familiar_brotherbobby&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void FireEvent(const float4& dir) override;
};

