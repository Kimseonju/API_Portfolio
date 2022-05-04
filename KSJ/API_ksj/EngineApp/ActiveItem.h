#pragma once
#include <EngineActor.h>
#include "CCharacterInfo.h"
//용도 :
//설명 :Item_haloofflies
class EngineRendererBasic;
class ActiveItem : public EngineActor
{
private: //static
public:  //static func
protected:
	EngineRendererBasic* m_RenderBody;
public:
public: //constructer destructer
	ActiveItem();
	virtual ~ActiveItem();


public:
	ActiveItem(const ActiveItem& _Other) = delete;
	ActiveItem(const ActiveItem&& _Other) = delete;

public:
	ActiveItem& operator=(const ActiveItem& _Other) = delete;
	ActiveItem& operator=(const ActiveItem&& _Other) = delete;

public: //member
	void Start() override;
	void Update() override;
	virtual void Play() {};
	virtual int ItemType() { return 0; };
};

