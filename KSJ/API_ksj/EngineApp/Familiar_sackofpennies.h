#pragma once
#include "Familiar.h"
//용도 :
//설명 :
class Familiar_sackofpennies : public Familiar
{
private: //static
public:  //static func
private:
public: //member



public: //constructer destructer
	Familiar_sackofpennies();
	~Familiar_sackofpennies();

public:
	Familiar_sackofpennies(const Familiar_sackofpennies& _Other) = delete;
	Familiar_sackofpennies(const Familiar_sackofpennies&& _Other) = delete;

public:
	Familiar_sackofpennies& operator=(const Familiar_sackofpennies& _Other) = delete;
	Familiar_sackofpennies& operator=(const Familiar_sackofpennies&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void FamiliarEvent() override;
};

