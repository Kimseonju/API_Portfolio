#include "TitleScene.h"
#include "TitleBackGround_ksj.h"
#include <EngineWindow.h>
#include <EngineInput.h>
#include "Core.h"
#include "Title_Title.h"
#include "Title_Start.h"
#include <EngineMovie.h>
#include <EngineDirectory.h>
#include "SelectBackGround.h"
#include "SelectMouse.h"
#include "SelectFadeIn.h"
#include "TitleBackSelect.h"
// Static Var
// Static Func

// member Var
TitleScene::TitleScene()
	:m_SelectMouse(nullptr)
	, GameStart(true)
	, m_Select(false)
	, m_Title(true)
	, m_CamTime(0.f)
	, m_CamMove(false)
	, m_CamStartPos(float4::ZERO)
	, m_CamEndPos(float4::ZERO)
	, m_SelectBack(nullptr)

{

}

TitleScene::~TitleScene()
{

}
// member Func

void TitleScene::Start()
{

	//시작화면
	{
		TitleBackGround_ksj* Object = CreateActor<TitleBackGround_ksj>();
		Object->SetPosition(EngineWindow::GetSize().hfloat4());
	}

	{
		Title_Title* Object = CreateActor<Title_Title>();
		Object->SetPosition(EngineWindow::GetSize().hfloat4());
	}

	{
		Title_Start* Object = CreateActor<Title_Start>();
		float4 pos = EngineWindow::GetSize().hfloat4();
		Object->SetPosition(EngineWindow::GetSize().hfloat4());
	}
	//카메라이동으로 아래로가자
	{
		SelectBackGround* Object = CreateActor<SelectBackGround>();
		float4 pos = EngineWindow::GetSize().hfloat4();
		pos.y += pos.y * 2;
		Object->SetPosition(pos);
	}


	{
		m_SelectBack = CreateActor< TitleBackSelect>();

	}
	{
		m_SelectMouse = CreateActor<SelectMouse>();
	}

	EngineSound::Play(L"TitleBGM.mp3", true, 0);
	EngineSound::Volume(L"TitleBGM.mp3", 0.7f);
}
void TitleScene::SceneUpdate()
{
	MapMove();
	if (m_CamMove)
		return;



	if (true==m_Title)
	{
		if (true == EngineInput::IsUp(L"Enter"))
		{
			EngineSound::Play(L"BookPageTurn.mp3", false, 0);
			//Core::SceneManager.ChangeScene(L"SelectScene");
			m_Title = false;
			m_CamStartPos = float4::ZERO;
			m_CamEndPos.y = EngineWindow::GetSize().y;
			m_CamTime = 0.f;
			m_CamMove = true;
			m_SelectBack->MoveStart(true);
		}
	}
	
	

	else
	{
		if (true == EngineInput::IsUp(L"ESC"))
		{
			EngineSound::Play(L"BookPageTurn.mp3", false, 0);
			m_CamStartPos = GetCamPos();
			m_CamEndPos = float4::ZERO;
			m_Title = true;
			m_CamTime = 0.f;
			m_CamMove = true;
			m_SelectBack->MoveStart(false);
		}

		if (true == EngineInput::IsUp(L"UFire")
			|| true == EngineInput::IsUp(L"DFire"))
		{
			GameStart = GameStart ? false : true; 
			EngineSound::Play(L"character_select_right.mp3", false, 0);
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
			float4 size = EngineWindow::GetSize();
			size.x = size.x / 2.78f;
			size.y = size.y / 3.f;
			size.y += EngineWindow::GetSize().y;
			m_SelectMouse->SetPosition({ size });
		}
		else
		{
			float4 size = EngineWindow::GetSize();
			size.x = size.x / 2.6f;
			size.y = size.y / 1.76f; 
			size.y += EngineWindow::GetSize().y;
			m_SelectMouse->SetPosition({ size });
		}
	}
	


}
void TitleScene::MapMove()
{

	if (true == m_CamMove)
	{
		m_CamTime += EngineTimer::FDeltaTime(3);
		float4 CurPos = float4::Lerp2DMax(m_CamStartPos, m_CamEndPos, m_CamTime);
		SetCamPos(CurPos);
		if (1.0F <= m_CamTime)
		{
			m_CamMove = false;
		}
	}
}