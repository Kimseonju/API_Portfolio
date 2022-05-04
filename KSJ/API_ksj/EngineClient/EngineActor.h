#pragma once
#include <EngineMath.h>
#include <list>
#include "EngineScene.h"
#include <EngineWindow.h>
#include <EngineObjectBase.h>
// �з� : 
// �뵵 : 
// ���� : ����� �̷�� ���� ������ ��ҵ鿡�� ��ɵ� �����ϴ� Ŭ����
//������ ���� �������ִ�.
class EngineCollision;
class EngineScene;
class EngineRenderer;
class EngineActor : public EngineObjectBase
{
    friend EngineScene;
private:
public:
private:
    EngineScene* m_Scene;

    float4 m_Position;
    float4 m_Size;
    EngineString m_ClassType;
public:

    EngineString& GetClassType()
    {
        return m_ClassType;
    }

    void SetClassType(const EngineString& _Type)
    {
        m_ClassType = _Type;
    }

    EngineScene* GetScene() {
        return m_Scene;
    }

    void SetScene(EngineScene* _Scene)
    {
        m_Scene = _Scene;
    }

    float4 GetCamPosition() {
        return  GetPosition() - m_Scene->GetCamPos();
    }
    float4 GetPosition()
    {
        if (nullptr == GetParentBase() || this == GetParentBase())
        {
            return m_Position;
        }
        return GetParentBase()->GetPosition()+m_Position;
    }

    float4 GetNotParentPosition()
    {
        return m_Position;
    }
    void SetPosition(const float4& _Other)
    {
        m_Position = _Other;
    }

    float4 GetSize() const
    {
        return m_Size;
    }
    void SetSize(const float4& _Other)
    {
        m_Size = _Other;
    }

    void MovePosition(const float4& _Other)
    {
        m_Position += _Other;
    }
public:
    std::list<EngineRenderer*> m_Renderer;

public:

    //����������
    // _Order ������ ������ �ǹ�
    template<typename T>
    T* CreateRenderer(int _Order)
    {
        T* NewT = new T();
        NewT->SetOrder(_Order);

        NewT->SetActor(this);
        NewT->SetParentBase(this);
        m_Renderer.push_back(NewT);
        m_Scene->PushRenderer(NewT);
        return NewT;
    }


    //�浹����

    std::list<EngineCollision*> m_Collision;

public:
    template<typename T>
    T* CreateCollision(int _Order)
    {
        T* NewT = new T();
        NewT->SetOrder(_Order);

        NewT->SetActor(this);
        NewT->SetParentBase(this);
        m_Collision.push_back(NewT);
        m_Scene->PushCollision(NewT);
        return NewT;
    }


    void DebugTextout(EngineString& _string, int _x, int _y)
    {
        TextOut(EngineWindow::GetBackBufferDC(), _x, _y, _string.c_str(), lstrlen(_string.c_str()));
    }

    
public: 
    EngineActor();
    virtual ~EngineActor();

public: 
    EngineActor(const EngineActor& _Other) = delete;
    EngineActor(const EngineActor&& _Other) = delete;

public: 
    EngineActor& operator=(const EngineActor& _Other) = delete;
    EngineActor& operator=(const EngineActor&& _Other) = delete;

public:
    virtual void Start() {}
    virtual void CollisionPrev() {}
    virtual void CollisionNext() {}

    virtual void UpdateUI() {}
    virtual void UpdatePrev() {} 
    virtual void Update() {} 
    virtual void UpdateNext() {} 

    virtual void RenderPrev() {} 
    virtual void Render() {}
    virtual void RenderNext() {} 

    virtual void DebugRender() {}

    void DeathTask() override;

    // �̹������ӿ� ���� off�Ǿ�߸� ȣ���� �Ǿ�� ����?
    void OffTask() override;
    virtual void OnTask();
private:
    virtual void Release();
};

