#include "SelectScene.h"
#include <EngineWindow.h>
#include <EngineInput.h>
#include "Core.h"
#include "SelectBackGround.h"
#include "SelectMouse.h"
#include "SelectFadeIn.h"
// Static Var
// Static Func

// member Var
SelectScene::SelectScene()
	:m_SelectMouse(nullptr)
	,GameStart(true)
	, m_Select(false)
{

}

SelectScene::~SelectScene()
{

}
// member Func

void SelectScene::Start()
{

	{
		SelectBackGround* Object = CreateActor<SelectBackGround>();
		Object->SetPosition(EngineWindow::GetSize().hfloat4());
	}

	{
		m_SelectMouse = CreateActor<SelectMouse>();
	}
}
void SelectScene::SceneChangeEnd()
{
}
void SelectScene::SceneUpdate()
{
	if (true == EngineInput::IsUp(L"UFire"))
	{
		GameStart = GameStart ? false : true;
	}
	if (true == EngineInput::IsUp(L"DFire"))
	{
		GameStart = GameStart ? false : true;
	}
	if (true == EngineInput::IsUp(L"Enter"))
	{
		if (GameStart)
		{
			if (!m_Select)
			{
				EngineSound::Stop(L"TitleBGM.mp3");
				EngineSound::Play(L"GamePlayLoading.mp3", false, 0);
				EngineSound::Volume(L"GamePlayLoading.mp3", 0.7f);
				m_Select = true;
				CreateActor<SelectFadeIn>();
			}
		}
		else
		{
			EngineWindow::WindowEnd();
		}
	}
	if (GameStart)
	{
		float4 size=EngineWindow::GetSize();
		size.x = size.x/2.78f;
		size.y = size.y /3.f;
		m_SelectMouse->SetPosition({ size });
	}
	else
	{
		float4 size = EngineWindow::GetSize();
		size.x = size.x / 2.6f;
		size.y = size.y / 1.76f;
		m_SelectMouse->SetPosition({ size });
	}
}