#include "BoxItem.h"
#include <EngineCollision.h>
#include "LogicValue.h"
#include "Player.h"
//static
//static func

void BoxItem::SpawnStart()
{
	m_RenderBody->ChangeAnimation(L"Spawn");

}

void BoxItem::SpawnStay()
{
	if (m_RenderBody->IsEndAni())
	{
		m_BoxItemFSM.ChangeState(L"Idle");
	}
}

void BoxItem::SpawnEnd()
{
}

void BoxItem::IdleStart()
{
	m_RenderBody->ChangeAnimation(L"Idle");
}

void BoxItem::IdleStay()
{
}

void BoxItem::IdleEnd()
{
}

void BoxItem::OpenStart()
{
	m_RenderBody->ChangeAnimation(L"Open");
}

void BoxItem::OpenStay()
{
}

void BoxItem::OpenEnd()
{
}


void BoxItem::StartCol(EngineCollision* _This, EngineCollision* _Other)
{

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player))
	{
		Player* player = LogicValue::MainPlayer;
		if (m_ItemType == LogicValue::ItemBoxType::Treasure_box)
		{
			if (player->GetCharacterInfo()->GetKey() > 0)
			{
				if (m_KeyCount > 0)
				{
					player->GetCharacterInfo()->KeySub();
					m_KeyCount -= 1;
					//키돌아가는 소리
				}
			}
		}
	}

	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		if (m_ItemType == LogicValue::ItemBoxType::BombAttack_box)
		{
			if (m_KeyCount > 0)
			{
				m_KeyCount -= 1;
			}
		}
	}

	else if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Bomb))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		Dir.Normalize();
		m_CharacterInfo->DamageAccel(Dir, 2.f);
	}
}

void BoxItem::EndCol(EngineCollision* _This, EngineCollision* _Other)
{
}

void BoxItem::StayCol(EngineCollision* _This, EngineCollision* _Other)
{
	if (_Other->GetOrder() == static_cast<int>(LogicValue::CollisionGroup::Player))
	{
		float4 Dir = _This->GetPosition() - _Other->GetPosition();
		m_CharacterInfo->AccelSpeedMove(Dir, 0.8f);

	}
}
