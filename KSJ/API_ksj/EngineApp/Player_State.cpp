#include "Player.h"
#include <EngineRendererAnim.h>
#include <EngineInput.h>
#include <EngineWindowResMgr.h>
#include "Tears.h"
#include "LogicValue.h"
#include <EngineCollision.h>
void Player::MapCollision()
{
	EngineWinImage* FindImage = EngineWindowResMgr::Inst().FindImage(L"MapCollider.bmp");
	float4 PlayerMovePos = m_CharacterInfo->GetUpdateSpeed();
	bool bDoorEntrance = false;
	//임시충돌 수정필요
	if (nullptr != FindImage)
	{

		if (!m_CamMove)
		{
			float4 CheckPos = GetPosition() + PlayerMovePos;
			CheckPos.x -= m_MapCount.x * 960;
			CheckPos.y -= m_MapCount.y * 540;

			//무조건 정지
			bool CollisionRed = false;
			float4 Pos = { CheckPos + m_BodyCol->GetPivotPos() };


			float4 DirPos[4];
			DirPos[0].x = Pos.x - m_BodyCol->GetScale().ihx();
			DirPos[0].y = Pos.y;

			DirPos[1].x = Pos.x + m_BodyCol->GetScale().ihx();
			DirPos[1].y = Pos.y;

			DirPos[2].x = Pos.x;
			DirPos[2].y = Pos.y - m_BodyCol->GetScale().ihy();

			DirPos[3].x = Pos.x;
			DirPos[3].y = Pos.y + m_BodyCol->GetScale().ihy();
			for (int DirPosNum = 0; DirPosNum < 4; ++DirPosNum)
			{
				for (int DirNum = 0; DirNum < 4; ++DirNum)
				{

					int CheckColor = FindImage->GetPixelColor(DirPos[DirPosNum].ix(), DirPos[DirPosNum].iy());
					if (RGB(200, 0, 0) == CheckColor)
					{
						CollisionRed = true;
					}
					//벽방향
					if (RGB(200 + float4::AllDir[DirNum].ix(), 200 + float4::AllDir[DirNum].iy(), 0) == CheckColor)
					{
						if (DirNum == 0 || DirNum == 1)
							m_WallLeftRightCollision = (Dir)DirNum;
						else
							m_WallUpDownCollision = (Dir)DirNum;
					}
					//문입구방향
					if (RGB(100 + float4::AllDir[DirNum].ix(), 100 + float4::AllDir[DirNum].iy(), 0) == CheckColor)
					{
						float4 MapCount = m_MapCount;
						MapCount = MapCount + float4::AllDir[DirNum];
						//문이없다.
						if (static_cast<int>(LogicValue::RoomType::Max) == GetScene()->GetMapCheck(MapCount) || !GetScene()->GetMapClear(m_MapCount))
						{
							if (DirNum == 0 || DirNum == 1)
								m_WallLeftRightCollision = (Dir)DirNum;
							else
								m_WallUpDownCollision = (Dir)DirNum;
						}
						else
						{
							bDoorEntrance = true;
						}
					}
					//문입장
					if (RGB(150 + float4::AllDir[DirNum].ix(), 150 + float4::AllDir[DirNum].iy(), 0) == CheckColor)
					{
						CamMoveCheck(float4::AllDir[DirNum]);
					}

				}
			}


			if (m_WallLeftRightCollision != Dir::MAX)
			{
				if (m_WallLeftRightCollision == Dir::LEFT)
				{
					if (m_CharacterInfo->GetDir().x != 1.f)
					{
						m_CharacterInfo->StopX();
					}
					if (bDoorEntrance)
						MovePosition({ 1.f,0.f });
				}
				if (m_WallLeftRightCollision == Dir::RIGHT)
				{
					if (m_CharacterInfo->GetDir().x != -1.f)
					{
						m_CharacterInfo->StopX();
					}
					if (bDoorEntrance)
						MovePosition({ -1.f,0.f });
				}
			}
			if (m_WallUpDownCollision != Dir::MAX)
			{
				if (m_WallUpDownCollision == Dir::UP)
				{
					if (m_CharacterInfo->GetDir().y != 1.f)
					{
						m_CharacterInfo->StopY();
					}
					if (bDoorEntrance)
						MovePosition({ 0.f,1.f });
				}
				if (m_WallUpDownCollision == Dir::DOWN)
				{
					if (m_CharacterInfo->GetDir().y != -1.f)
					{
						m_CharacterInfo->StopY();
					}
					if (bDoorEntrance)
						MovePosition({ 0.f,-1.f });
				}
			}
			if (CollisionRed)
			{
				m_CharacterInfo->StopX();
				m_CharacterInfo->StopY();
			}
			m_WallLeftRightCollision = Dir::MAX;
			m_WallUpDownCollision = Dir::MAX;
		}
	}
}