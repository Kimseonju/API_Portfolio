#pragma once
#include <EngineScene.h>
// �з� : Scene
// �뵵 : ����ȭ�� (���ȭ��)
// ���� : ���ӷΰ� �߰��ϴ� Ŭ����
class FadeInOutChange;
class SelectScene : public EngineScene
{
private: // Static Var
public: // Static Func
private: // member Var
    bool m_Select;
    bool GameStart;
    EngineActor* m_SelectMouse;
public: // constructer destructer
    SelectScene();
    ~SelectScene();
public: // delete constructer 
    SelectScene(const SelectScene& _Other) = delete;
    SelectScene(const SelectScene&& _Other) = delete;

public: // delete operator
    SelectScene& operator=(const SelectScene& _Other) = delete;
    SelectScene& operator=(const SelectScene&& _Other) = delete;

public: // member Func
    void SceneUpdate() override;
    void Start() override;
    void SceneChangeEnd() override;
};
