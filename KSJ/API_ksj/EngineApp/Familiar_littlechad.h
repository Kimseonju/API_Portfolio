#pragma once
#include "Familiar.h"
//용도 :
//설명 :
class Familiar_littlechad : public Familiar
{
private: //static
public:  //static func
private:
public: //member



public: //constructer destructer
	Familiar_littlechad();
	~Familiar_littlechad();

public:
	Familiar_littlechad(const Familiar_littlechad& _Other) = delete;
	Familiar_littlechad(const Familiar_littlechad&& _Other) = delete;

public:
	Familiar_littlechad& operator=(const Familiar_littlechad& _Other) = delete;
	Familiar_littlechad& operator=(const Familiar_littlechad&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void FamiliarEvent() override;
};

