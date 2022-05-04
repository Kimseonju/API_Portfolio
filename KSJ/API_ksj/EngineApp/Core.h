#pragma once
#include <EngineScene.h>
#include <EngineString.h>
#include <map>
#include <EngineSceneManager.h>

// �з� : ������ 
// �뵵 : �������� or �Ŵ���(Scene ����)
// ���� : ������ ������ �����ϰ� ������ �������� ������ ������ Ŭ����
class Core
{
private: // Static Var
public: // Static Func

    static EngineSceneManager SceneManager;

private: // member Var

    std::map<EngineString, EngineScene*> m_AllScene;

private: // constructer destructer
    Core();
    ~Core();
public: // delete constructer 
    Core(const Core& _Other) = delete;
    Core(const Core&& _Other) = delete;

public: // delete operator
    Core& operator=(const Core& _Other) = delete;
    Core& operator=(const Core&& _Other) = delete;

public: // member Func
    static void Start();
    static void Update();

    static void KeyInput();
    static void ImageCut();
    static void End();
};

