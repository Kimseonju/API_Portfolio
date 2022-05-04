#include "EngineScene.h"
#include "EngineActor.h"
#include <EngineWindow.h>
#include "EngineRenderer.h"
#include "EngineCollision.h"
#include <EngineMath.h>
#include <EngineMovie.h>
EngineScene::EngineScene() :m_Debug(false)
, CamPos(float4::ZERO)
, m_Pause(false)
{

}

EngineScene::~EngineScene()
{
	std::list<EngineActor*>::iterator Start = m_Actors.begin();
	std::list<EngineActor*>::iterator End = m_Actors.end();
	for (; Start != End; ++Start)
	{
		if (nullptr != *Start)
		{
			delete* Start;
			*Start = nullptr;
		}
	}
	m_Actors.clear();
}

void EngineScene::Progress()
{

	SceneUpdate();

	{ //UI이펙트용 업데이트 Pause 영향안받음
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}
			(*Start)->UpdateUI();
		}
	}

	{
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}
			if (m_Pause)
			{
				continue;
			}
			(*Start)->UpdatePrev();
		}
	}

	{
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}
			if (m_Pause)
			{
				continue;
			}
			(*Start)->Update();
		}
	}

	CollisionProcess();



	{
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}
			if (m_Pause)
			{
				continue;
			}
			(*Start)->UpdateNext();
		}
	}

	SceneLateUpdate();
	{
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{
			if (false == (*Start)->IsOn())
			{
				continue;
			}
			if (m_Pause)
			{
				continue;
			}

			(*Start)->RenderPrev();
		}
	}


	if (false == EngineMovie::IsPlay())
	{
		Render();
		EngineWindow::BackBufferCopy();
	}

	OnOffCheck();
	Release();
}




//렌더링
void EngineScene::PushRenderer(EngineRenderer* _Renderer)
{
	if (m_RendererLists.end() == m_RendererLists.find(_Renderer->GetOrder()))
	{
		m_RendererLists.insert(std::map<int, std::list<EngineRenderer*>>::value_type(_Renderer->GetOrder(), std::list<EngineRenderer*>()));
	}

	m_RendererLists[_Renderer->GetOrder()].push_back(_Renderer);
}

void EngineScene::Render()
{


	


	////0~100 ,10000~ 시스템용 렌더러
	////y값커져서 수정..
	////0 배경
	////1 UI
	////2~5 UI위로 겹치는UI
	////10000 눈물
	////6 불오브젝트
	////화면크기 960 540
	////렌더러 순서 자동변경 101번째부터 900번쨰까지 y값기준으로 변경
	////
	////저장할 변수
	//std::map<int, std::list<EngineRenderer*>> RendererLists;
	//
	//std::map<int, std::list<EngineRenderer*>>::iterator LayerStart = m_RendererLists.begin();
	//std::map<int, std::list<EngineRenderer*>>::iterator LayerEnd = m_RendererLists.end();
	//for (; LayerStart != LayerEnd; ++LayerStart)
	//{
	//	std::list<EngineRenderer*>& _RenderLayer = LayerStart->second;
	//	std::list<EngineRenderer*>::iterator RendererStart = _RenderLayer.begin();
	//	std::list<EngineRenderer*>::iterator RendererEnd = _RenderLayer.end();
	//	for (; RendererStart != RendererEnd; ++RendererStart)
	//	{
	//		if ((*RendererStart)->GetOrder() > 100 && (*RendererStart)->GetOrder() < 10000)
	//		{
	//			(*RendererStart)->SetPositionYOrder();
	//		}
	//		if (RendererLists.end() == RendererLists.find((*RendererStart)->GetOrder()))
	//		{
	//			RendererLists.insert(std::map<int, std::list<EngineRenderer*>>::value_type((*RendererStart)->GetOrder(), std::list<EngineRenderer*>()));
	//		}
	//		RendererLists[(*RendererStart)->GetOrder()].push_back((*RendererStart));
	//	}
	//	(_RenderLayer).clear();
	//	
	//}
	////y값기준정렬완료
	//m_RendererLists.clear();
	//m_RendererLists = RendererLists;
	//
	//
	//
	//
	//
	//
	//std::map<int, std::list<EngineRenderer*>>::iterator LayerStart = m_RendererLists.begin();
	//std::map<int, std::list<EngineRenderer*>>::iterator LayerEnd = m_RendererLists.end();
	//
	//for (; LayerStart != LayerEnd; ++LayerStart)
	//{
	//	std::list<EngineRenderer*>& _RenderLayer = LayerStart->second;
	//
	//	std::list<EngineRenderer*>::iterator RendererStart = _RenderLayer.begin();
	//	std::list<EngineRenderer*>::iterator RendererEnd = _RenderLayer.end();
	//
	//	for (; RendererStart != RendererEnd; ++RendererStart)
	//	{
	//		if (false == (*RendererStart)->IsOn())
	//		{
	//			continue;
	//		}
	//
	//		(*RendererStart)->Render();
	//	}
	//
	//}



	//0~100 ,10000~ 시스템용 렌더러
	//y값커져서 수정..
	//0 배경
	//1 UI
	//2~5 UI위로 겹치는UI
	//10000 눈물
	//6 불오브젝트
	//화면크기 960 540
	//렌더러 순서 자동변경 101번째부터 900번쨰까지 y값기준으로 변경
	//
	//저장할 변수
	std::multimap<float, EngineRenderer*> multiRendererLists;
	{
		std::map<int, std::list<EngineRenderer*>>::iterator LayerStart = m_RendererLists.begin();
		std::map<int, std::list<EngineRenderer*>>::iterator LayerEnd = m_RendererLists.end();
		for (; LayerStart != LayerEnd; ++LayerStart)
		{
			std::list<EngineRenderer*>& _RenderLayer = LayerStart->second;
			std::list<EngineRenderer*>::iterator RendererStart = _RenderLayer.begin();
			std::list<EngineRenderer*>::iterator RendererEnd = _RenderLayer.end();
			for (; RendererStart != RendererEnd; ++RendererStart)
			{
				if ((*RendererStart)->GetOrder() > 100 && (*RendererStart)->GetOrder() < 10000)
				{
					multiRendererLists.insert(std::multimap<float, EngineRenderer*>::value_type((*RendererStart)->GetActor()->GetPosition().y + 100.f, (*RendererStart)));
				}
				else
				{
					multiRendererLists.insert(std::multimap<float, EngineRenderer*>::value_type((float)(*RendererStart)->GetOrder(), (*RendererStart)));
				}
				
			}

		}
	}






	std::multimap<float, EngineRenderer*>::iterator LayerStart = multiRendererLists.begin();
	std::multimap<float, EngineRenderer*>::iterator LayerEnd = multiRendererLists.end();

	for (; LayerStart != LayerEnd; ++LayerStart)
	{

		if (false == (*LayerStart).second->IsOn())
		{
			continue;
		}

		(*LayerStart).second->Render();


	}

	{
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{

			if (false == (*Start)->IsOn())
			{
				continue;
			}
			if (m_Debug)
				(*Start)->DebugRender();
		}
		if(m_Debug)
			SceneDebugRender();
	}
	{
		std::map<int, std::list<EngineCollision*>>::iterator Start = m_CollisionLists.begin();
		std::map<int, std::list<EngineCollision*>>::iterator End = m_CollisionLists.end();

		for (; Start != End; ++Start)
		{
			std::list<EngineCollision*>::iterator StartCol = Start->second.begin();
			std::list<EngineCollision*>::iterator EndCol = Start->second.end();
			for (; StartCol != EndCol; ++StartCol)
			{
				if (false == (*StartCol)->IsOn())
				{
					continue;
				}
				if (m_Debug)
					(*StartCol)->Render();
			}
		}
	}
}


//충돌
void EngineScene::PushCollision(EngineCollision* _Collision)
{
	if (m_CollisionLists.end() == m_CollisionLists.find(_Collision->GetOrder()))
	{
		m_CollisionLists.insert(std::map<int, std::list<EngineCollision*>>::value_type(_Collision->GetOrder(), std::list<EngineCollision*>()));
	}

	m_CollisionLists[_Collision->GetOrder()].push_back(_Collision);


}

void EngineScene::CollisionProcess()
{

	std::map<int, std::list<EngineCollision*>>::iterator Start = m_CollisionLists.begin();
	std::map<int, std::list<EngineCollision*>>::iterator End = m_CollisionLists.end();

	for (; Start != End; ++Start)
	{
		std::list<EngineCollision*>::iterator StartCol = Start->second.begin();
		std::list<EngineCollision*>::iterator EndCol = Start->second.end();
		for (; StartCol != EndCol; ++StartCol)
		{
			if (false == (*StartCol)->IsOn())
			{
				continue;
			}
			(*StartCol)->CollisionDataUpdate();
		}
	}



	std::map<int, std::set<int>>::iterator LeftGroupStart = m_LinkCollsionGroup.begin();
	std::map<int, std::set<int>>::iterator LeftGroupEnd = m_LinkCollsionGroup.end();

	for (; LeftGroupStart != LeftGroupEnd; ++LeftGroupStart)
	{
		std::set<int>::iterator RightGroupStart = LeftGroupStart->second.begin();
		std::set<int>::iterator RightGroupEnd = LeftGroupStart->second.end();

		for (; RightGroupStart != RightGroupEnd; ++RightGroupStart)
		{
			int LeftGroupIndex = LeftGroupStart->first;
			int RightGroupIndex = *RightGroupStart;

			if (LeftGroupIndex != RightGroupIndex)
			{
				CollisionGroupOtherCheck(LeftGroupIndex, RightGroupIndex);
			}

			else
			{
				CollisionGroupThisCheck(LeftGroupIndex);
			}
		}
	}
}

void EngineScene::CollisionGroupOtherCheck(int _Left, int _Right)
{
	std::list<EngineCollision*>& LeftGroup = m_CollisionLists[_Left];
	std::list<EngineCollision*>& RightGroup = m_CollisionLists[_Right];

	std::list<EngineCollision*>::iterator LeftStartIter = LeftGroup.begin();
	std::list<EngineCollision*>::iterator LeftEndIter = LeftGroup.end();

	for (; LeftStartIter != LeftEndIter; ++LeftStartIter)
	{
		if (false == (*LeftStartIter)->IsOn())
		{
			continue;
		}
		std::list<EngineCollision*>::iterator RightStartIter = RightGroup.begin();
		std::list<EngineCollision*>::iterator RightEndIter = RightGroup.end();

		for (; RightStartIter != RightEndIter; ++RightStartIter)
		{
			if (false == (*RightStartIter)->IsOn())
			{
				continue;
			}
			(*LeftStartIter)->CollisionCheck(*RightStartIter);
		}
	}

}

void EngineScene::CollisionGroupThisCheck(int _Value)
{
	std::list<EngineCollision*>& LeftGroup = m_CollisionLists[_Value];

	std::list<EngineCollision*>::iterator LeftStartIter = LeftGroup.begin();
	std::list<EngineCollision*>::iterator LeftEndIter = LeftGroup.end();

	for (; LeftStartIter != LeftEndIter; ++LeftStartIter)
	{
		//중복비교방지를위해 현재값 넣기 가져오기
		if (false == (*LeftStartIter)->IsOn())
		{
			continue;
		}

		std::list<EngineCollision*>::iterator RightStartIter = LeftStartIter;
		std::list<EngineCollision*>::iterator RightEndIter = LeftGroup.end();

		for (; RightStartIter != RightEndIter; ++RightStartIter)
		{
			if (false == (*RightStartIter)->IsOn())
			{
				continue;
			}

			if (LeftStartIter == RightStartIter)
			{//만약 처음 비교하는거라면 (같다면)
				continue;
			}
			(*LeftStartIter)->CollisionCheck(*RightStartIter);
		}
	}
}
void EngineScene::OnOffCheck() {
	// 랜더러 정리
	{
		std::map<int, std::list<EngineRenderer*>>::iterator LayerStart = m_RendererLists.begin();
		std::map<int, std::list<EngineRenderer*>>::iterator LayerEnd = m_RendererLists.end();

		for (; LayerStart != LayerEnd; ++LayerStart)
		{
			std::list<EngineRenderer*>& _RenderLayer = LayerStart->second;
			std::list<EngineRenderer*>::iterator RendererStart = _RenderLayer.begin();
			std::list<EngineRenderer*>::iterator RendererEnd = _RenderLayer.end();

			for (; RendererStart != RendererEnd; ++RendererStart)
			{
				(*RendererStart)->CallOnTask();
				(*RendererStart)->CallOffTask();
			}

		}
	}

	// 충돌체 정리
	{
		std::map<int, std::list<EngineCollision*>>::iterator Start = m_CollisionLists.begin();
		std::map<int, std::list<EngineCollision*>>::iterator End = m_CollisionLists.end();

		for (; Start != End; ++Start)
		{
			std::list<EngineCollision*>::iterator StartCol = Start->second.begin();
			std::list<EngineCollision*>::iterator EndCol = Start->second.end();

			for (; StartCol != EndCol; ++StartCol)
			{
				(*StartCol)->CallOnTask();
				(*StartCol)->CallOffTask();
			}
		}
	}

	{
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{
			(*Start)->CallOnTask();
			(*Start)->CallOffTask();
		}
	}
}

void EngineScene::Release()
{//랜더러

	{
		std::map<int, std::list<EngineRenderer*>>::iterator LayerStart = m_RendererLists.begin();
		std::map<int, std::list<EngineRenderer*>>::iterator LayerEnd = m_RendererLists.end();

		for (; LayerStart != LayerEnd; ++LayerStart)
		{
			std::list<EngineRenderer*>& _RenderLayer = LayerStart->second;
			std::list<EngineRenderer*>::iterator RendererStart = _RenderLayer.begin();
			std::list<EngineRenderer*>::iterator RendererEnd = _RenderLayer.end();

			for (; RendererStart != RendererEnd; ++RendererStart)
			{
				(*RendererStart)->CallOffTask();
			}
		}
	}

	//충돌체
	{
		std::map<int, std::list<EngineCollision*>>::iterator Start = m_CollisionLists.begin();
		std::map<int, std::list<EngineCollision*>>::iterator End = m_CollisionLists.end();

		for (; Start != End; ++Start)
		{
			std::list<EngineCollision*>::iterator StartCol = Start->second.begin();
			std::list<EngineCollision*>::iterator EndCol = Start->second.end();

			for (; StartCol != EndCol; ++StartCol)
			{
				(*StartCol)->CallOffTask();
			}
		}
	}
	{//Release 단계 실행 액터
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; ++Start)
		{
			(*Start)->CallOffTask();
		}
	}

	{
		std::map<int, std::list<EngineRenderer*>>::iterator LayerStart = m_RendererLists.begin();
		std::map<int, std::list<EngineRenderer*>>::iterator LayerEnd = m_RendererLists.end();

		for (; LayerStart != LayerEnd; ++LayerStart)
		{
			std::list<EngineRenderer*>& _RenderLayer = LayerStart->second;
			std::list<EngineRenderer*>::iterator RendererStart = _RenderLayer.begin();
			std::list<EngineRenderer*>::iterator RendererEnd = _RenderLayer.end();

			for (; RendererStart != RendererEnd;)
			{
				if (false == (*RendererStart)->IsDeath())
				{
					++RendererStart;
					continue;
				}
				// (*RendererStart)->DeathTask();
				RendererStart = _RenderLayer.erase(RendererStart);
			}
		}
	}

	//충돌체
	{
		std::map<int, std::list<EngineCollision*>>::iterator Start = m_CollisionLists.begin();
		std::map<int, std::list<EngineCollision*>>::iterator End = m_CollisionLists.end();

		for (; Start != End; ++Start)
		{
			std::list<EngineCollision*>::iterator StartCol = Start->second.begin();
			std::list<EngineCollision*>::iterator EndCol = Start->second.end();

			for (; StartCol != EndCol; )
			{
				if (false == (*StartCol)->IsDeath())
				{
					++StartCol;
					continue;
				}
				// (*StartCol)->DeathTask();
				StartCol = Start->second.erase(StartCol);
			}
		}
	}


	{//Release 단계 실행 액터
		std::list<EngineActor*>::iterator Start = m_Actors.begin();
		std::list<EngineActor*>::iterator End = m_Actors.end();
		for (; Start != End; )
		{
			if (false == (*Start)->IsDeath())
			{
				(*Start)->Release();
				++Start;
				continue;
			}
			(*Start)->DeathTask();
			delete (*Start);
			Start = m_Actors.erase(Start);
		}
	}
}

void EngineScene::SceneUpdate()
{
}
