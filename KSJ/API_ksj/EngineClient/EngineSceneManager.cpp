#include "EngineSceneManager.h"
#include <EngineDebug.h>

EngineSceneManager::EngineSceneManager() : m_CurScene(nullptr), m_NextScene(nullptr)
{

}

EngineSceneManager::~EngineSceneManager()
{
	std::map<EngineString, EngineScene*>::iterator Start = m_AllScene.begin();
	std::map<EngineString, EngineScene*>::iterator End = m_AllScene.end();
	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			delete Start->second;
			Start->second = nullptr;
		}
	}
	m_AllScene.clear();
}

EngineScene* EngineSceneManager::FindScene(const EngineString& _Name)
{
	if (m_AllScene.end() == m_AllScene.find(_Name))
	{
		return nullptr;
	}
	return m_AllScene[_Name];
}

void EngineSceneManager::ChangeScene(const EngineString& _Name)
{
	m_NextScene = FindScene(_Name);

	if (nullptr == m_NextScene)
	{
		EngineDebug::AssertMsg(L"if (nullptr == m_NextScene)");
	}

}

void EngineSceneManager::ChangeCheck()
{
	if (nullptr != m_NextScene)
	{
		//¾À¹Ù²Ù±âÀü¿¡ ½ÇÇà
		if (nullptr != m_CurScene)
		{
			m_CurScene->SceneChangeEnd();
		}
		//¾À¹Ù²ÛÈÄ ½ºÅ¸Æ®
		m_CurScene = m_NextScene;
		m_CurScene->SceneChangeStart();

		m_NextScene = nullptr;
	}
}