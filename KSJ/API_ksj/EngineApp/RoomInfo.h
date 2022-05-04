#pragma once
#include <list>
#include <EngineMath.h>
#include "LogicValue.h"
#include <vector>
#include <map>
//�뵵 :
//���� :
class EngineActor;
class Enemy;
class PlayScene;
class Door;
class PlayBackGround;
class RoomInfo
{
private: //static
	static LogicValue::RoomInfoGroup RoomInfoGroups;
	static LogicValue::BossType BossSelectCount;

	static std::map<LogicValue::RoomInfoGroup, std::vector<std::pair<LogicValue::EditorActorType, float4>>> m_AllRoomInfoActor;

public:  //static func

	LogicValue::RoomInfoGroup GetInfoGroup()
	{
		return RoomInfoGroups;
	}
	void NextRoomInfo()
	{
		RoomInfoGroups = (LogicValue::RoomInfoGroup)(static_cast<int>(RoomInfoGroups) + 1);
		if (RoomInfoGroups == LogicValue::RoomInfoGroup::Max)
			RoomInfoGroups = LogicValue::RoomInfoGroup::Room1;
	}

	static void LoadRoom();
private:
	//��Ÿ��


	LogicValue::RoomType m_Type;
	float4 m_MapCount;
	PlayScene* m_Scene;
	Enemy* m_Boss;
	//EnemyŬ������ �����ϰ�;��µ�..
	std::list<Enemy*>m_AllEnemy;
	std::list<EngineActor*>m_AllObejct;
	std::list<EngineActor*>m_AllTear;
	
	//���� �� �׾���� �״� ������Ʈ
	std::list<Enemy*>m_AllEnemyInvincibility;
	
	std::vector<Door*>m_Door;
	Door* m_LeftDoor;
	Door* m_RightDoor;
	Door* m_UpDoor;
	Door* m_DownDoor;
	bool m_bDropItem;
	//����, ����������
	std::vector<EngineActor*>m_AllItem;
	//�����ֱ�� ����
	std::vector<float4>m_ItemPos;
	int m_ItemPosCount;
	//���� Ŭ�������� �ȵǾ��ִ���
	bool m_Clear;

	//���� ���� �ѹ���������

	bool m_bSoundClose;
	bool m_bSoundOpen;
public:
	void Init(const float4& _MapCount, PlayScene* _Scene);

	void SetType(LogicValue::RoomType _Type)
	{
		m_Type = _Type;
	}

	LogicValue::RoomType GetType()
	{
		return m_Type;
	}
	void PushEnemy(Enemy* _Enemy);
	void PushFinshBossEnemy(Enemy* _Enemy);
	void PushActor(EngineActor* _Actor);
	void PushTear(EngineActor* _Actor);
	void SetClear(bool _Clear)
	{
		m_Clear = _Clear;
	}
	bool GetClear()
	{
		return m_Clear;
	}
	int GetEnemySize()
	{
		return static_cast<int>(m_AllEnemy.size());
	}
	int GetFinshBossEnemySize()
	{
		return static_cast<int>(m_AllEnemyInvincibility.size());
	}

	
public: //constructer destructer
	RoomInfo();
	~RoomInfo();

public:
	RoomInfo(const RoomInfo& _Other) = delete;
	RoomInfo(const RoomInfo&& _Other) = delete;

public:
	RoomInfo& operator=(const RoomInfo& _Other) = delete;
	RoomInfo& operator=(const RoomInfo&& _Other) = delete;

public: //member

	void Start();
	void Play();
	void Stop();
	void Update();
	void LateUpdate();
	void EnemyAllKill();

	Enemy* TargetEnemyFind(EngineActor* _Other);
public:
	void DoorSoundOff()
	{
		m_bSoundClose = true;
		m_bSoundOpen = true;
	}

	Door* GetDoor(int _Num)
	{
		if (_Num == 0)
		{
			return m_LeftDoor;
		}
		else if (_Num == 1)
		{
			return m_RightDoor;
		}
		else if (_Num == 2)
		{
			return m_UpDoor;
		}
		else if (_Num == 3)
		{
			return m_DownDoor;
		}
		return nullptr;
	}
};

