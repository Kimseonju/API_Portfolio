#pragma once
#include <EngineBasePublic.h>
#include <EnginePlatformPublic.h>
#include <list>
#include <map>
#include <set>
#include <EngineWindow.h>

// �з� : ������Ʈ
// �뵵 : ��������(�ڱ� �ڽ��� �Լ����� ����), �Ŵ��� (���� ����)
// ���� : ����̶�� ������ ������� ����� �� ���信 ���� �⺻ ��ɵ��� �����ϴ� Ŭ����
//���� ����, ���� ������Ʈ, ������ �� ���Ͱ���, ī�޶� ��ġ ����
class EngineCollision;
class EngineRenderer;
class EngineActor;
class EngineScene
{
private:
public: 
private:

    
    std::list<EngineActor*> m_Actors;
    float4 CamPos;
    bool m_Debug;
    bool m_Pause;
public:

    void DebugOnOff()
    {
        m_Debug = !m_Debug;
    }

    void SetPause(bool _Pause)
    {
        m_Pause = _Pause;
    }
    float4 GetCamPos() {
        return CamPos;
    }

    void SetCamPos(const float4& _CamPos)
    {
        CamPos = _CamPos;
    }

    void SetCamMove(const float4& _CamPos)
    {
        CamPos += _CamPos;
    }

    template<typename ActorType>
    ActorType* CreateActor()
    {
        ActorType* NewActor = new ActorType();

        NewActor->SetScene(this);
        NewActor->Start();
        m_Actors.push_back(NewActor);
        return NewActor;
    }

public: 
    EngineScene();
    virtual ~EngineScene();
public: 
    EngineScene(const EngineScene& _Other) = delete;
    EngineScene(const EngineScene&& _Other) = delete;

public: 
    EngineScene& operator=(const EngineScene& _Other) = delete;
    EngineScene& operator=(const EngineScene&& _Other) = delete;

public: 
    virtual void Start() {}
    virtual int GetMapCheck(const float4& _Pos) { return 0; };
    virtual int GetMapCheck_Door(const float4& _Pos) { return 0; };
    virtual bool GetMapClear(const float4& _Pos) { return true; };
    void Progress();

private:
    std::map<int, std::list<EngineRenderer*>> m_RendererLists;

public:
    void PushRenderer(EngineRenderer* _Renderer);

private:
    void Render();


private:
    std::map<int, std::list<EngineCollision*>> m_CollisionLists;


    //set�� ������ ����� ã�µ� Ư��ȭ
    //set�� second�� ����
    std::map<int, std::set<int>>m_LinkCollsionGroup;

public:
    void CollisionGroupLink(int _Left, int _Right)
    {
        if (m_LinkCollsionGroup[_Left].end() != m_LinkCollsionGroup[_Left].find(_Right))
        {
            return;
        }

        m_LinkCollsionGroup[_Left].insert(_Right);
    }

    void PushCollision(EngineCollision* _Collision);
    
    void DebugTextout(EngineString& _string, int _x, int _y)
    {
        TextOut(EngineWindow::GetBackBufferDC(), _x, _y, _string.c_str(), lstrlen(_string.c_str()));
    }
private:
    void CollisionProcess();
    //Left���ִ� �׷�� Right�׷� �浹 ��
    void CollisionGroupOtherCheck(int _Left, int _Right);
    //���� �׷�
    void CollisionGroupThisCheck(int _Value);
public:

    void OnOffCheck();
    void Release();
public:
    virtual void SceneChangeStart() {}
    virtual void SceneChangeEnd() {}
    virtual void SceneUpdate();
    virtual void SceneLateUpdate() {}
    virtual void SceneDebugRender() {}
};