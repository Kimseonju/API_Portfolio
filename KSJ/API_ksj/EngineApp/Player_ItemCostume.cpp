#include "Player_ItemCostume.h"
#include <EngineRendererBasic.h>
#include <EngineInput.h>
#include <EngineTimer.h>
#include <EngineWindowResMgr.h>
#include <EngineRendererAnim.h>
Player_ItemCostume::Player_ItemCostume()
	:m_RenderHead(nullptr)
{

}

Player_ItemCostume::~Player_ItemCostume()
{

}
void Player_ItemCostume::ChangeAnimationdir(const EngineString& _dir)
{
	m_RenderHead->ChangeAnimation(_dir);
}
void Player_ItemCostume::FirstAnimationdir(const EngineString& _dir)
{
	m_RenderHead->FirstAnimation(_dir);
}
void Player_ItemCostume::FirstAnimationclear()
{
	m_RenderHead->FirstAnimationClear();
}
// member Func

void Player_ItemCostume::Start()
{


	m_RenderHead = CreateRenderer<EngineRendererAnim>(500);
	MovePosition({ 0,1 });
	//m_RenderHead->CreateAnimation(L"DownFire", L"costume_drfetus.bmp", 0, 1, 0.2f, true, false);
	//m_RenderHead->CreateAnimation(L"RightFire", L"costume_drfetus.bmp", 2, 3, 0.2f, true, false);
	//m_RenderHead->CreateAnimation(L"LeftFire", L"costume_drfetus.bmp", 6, 7, 0.2f, true, false);
	//m_RenderHead->CreateAnimation(L"UpFire", L"costume_drfetus.bmp", 4, 5, 0.2f, true, false);
	//
	//m_RenderHead->CreateAnimation(L"DownIdle", L"costume_drfetus.bmp", 1, 1, 0.2f, true, false);
	//m_RenderHead->CreateAnimation(L"RightIdle", L"costume_drfetus.bmp", 3, 3, 0.2f, true, false);
	//m_RenderHead->CreateAnimation(L"LeftIdle", L"costume_drfetus.bmp", 7, 7, 0.2f, true, false);
	//m_RenderHead->CreateAnimation(L"UpIdle", L"costume_drfetus.bmp", 4, 4, 0.2f, true, false);

}
void Player_ItemCostume::Update()
{
}

void Player_ItemCostume::SetAnimFrameTimer(float _Time)
{
	m_RenderHead->SetAllAnimTimer(_Time);
}

void Player_ItemCostume::SetCharacterFly()
{
	m_RenderHead->SetOrder(15000 + GetNotParentPosition().iy());

}
