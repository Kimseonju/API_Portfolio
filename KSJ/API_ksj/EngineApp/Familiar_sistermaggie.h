#pragma once
#include "Familiar.h"
//용도 :
//설명 :
class Familiar_sistermaggie : public Familiar
{
private: //static
public:  //static func
private:
public: //member



public: //constructer destructer
	Familiar_sistermaggie();
	~Familiar_sistermaggie();

public:
	Familiar_sistermaggie(const Familiar_sistermaggie& _Other) = delete;
	Familiar_sistermaggie(const Familiar_sistermaggie&& _Other) = delete;

public:
	Familiar_sistermaggie& operator=(const Familiar_sistermaggie& _Other) = delete;
	Familiar_sistermaggie& operator=(const Familiar_sistermaggie&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	void FireEvent(const float4& dir) override;
};

