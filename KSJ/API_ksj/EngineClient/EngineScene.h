#pragma once
#include <EngineBasePublic.h>
#include <EnginePlatformPublic.h>
#include <list>
#include <map>
#include <set>
#include <EngineWindow.h>

// 분류 : 오브젝트
// 용도 : 업데이터(자기 자신의 함수들을 실행), 매니저 (액터 관리)
// 설명 : 장면이라는 개념을 기능으로 만들고 그 개념에 대한 기본 기능들을 제공하는 클래스
//엑터 생성, 액터 업데이트, 렌더링 등 엑터관리, 카메라 위치 관리
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


    //set은 오로지 어떤값을 찾는데 특수화
    //set은 second가 없음
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
    //Left에있는 그룹과 Right그룹 충돌 비교
    void CollisionGroupOtherCheck(int _Left, int _Right);
    //같은 그룹
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