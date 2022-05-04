#pragma once
#include <EngineScene.h>
#include <vector>

#define MapX 6
#define MapY 6
// �з� : Scene
// �뵵 : ���� �÷��� ��
// ���� : ���� �÷��� ��

class BossUI;
class RoomInfo;
class Player;
class MiniMap;
class HPUI;
class BossAniActors;
class PlayScene : public EngineScene
{
private: // Static Var

public: // Static Func
private: // member Var
    std::vector<std::vector<RoomInfo*>> m_Map;
    MiniMap* m_MiniMap;
    HPUI* m_HPUI;
    float m_BossAniCount;
    float m_BossAniCountMax;
    bool m_bBossAni;
    BossAniActors* m_bossAniActor;
    BossUI* m_BossUI;
public: // constructer destructer
    PlayScene();
    ~PlayScene();

public: // delete constructer 
    PlayScene(const PlayScene& _Other) = delete;
    PlayScene(const PlayScene&& _Other) = delete;

public: // delete operator
    PlayScene& operator=(const PlayScene& _Other) = delete;
    PlayScene& operator=(const PlayScene&& _Other) = delete;

public: // member Func
    void Start() override;
    void SceneUpdate() override;
    void SceneLateUpdate() override;
    void SceneDebugRender() override;
public:
    BossUI* GetBossUI()
    {
        return m_BossUI;
    }
    int GetMapCheck(const float4& _Pos) override;
    int GetMapCheck_Door(const float4& _Pos)override;
    bool GetMapClear(const float4& _Pos) override;
    RoomInfo* GetMap(float4 map)
    {
        return GetMap(map.ix(), map.iy());
    }
    RoomInfo* GetMap(int x, int y)
    {
        if (0 > x || MapX <= x || 0 > y || MapY <= y) //�Ѿ����
            return nullptr;
        return m_Map[y][x];
    }

    void MiniMapRender();
};

