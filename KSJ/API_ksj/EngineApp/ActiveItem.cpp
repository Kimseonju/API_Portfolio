#include "ActiveItem.h"
#include <EngineRendererAnim.h>
#include <EngineCollision.h>
#include <EngineTimer.h>
#include "LogicValue.h"
#include <EngineRendererBasic.h>
//static
//static func


ActiveItem::ActiveItem() : m_RenderBody(nullptr)
{
}

ActiveItem::~ActiveItem()
{
}

void ActiveItem::Start()
{
	SetClassType(L"ActiveItem");
	m_RenderBody = CreateRenderer<EngineRendererBasic>(static_cast<int>(LogicValue::RenderGroup::UI));
	m_RenderBody->SetRenderScale({ 64,64 });

}

void ActiveItem::Update()
{


}

