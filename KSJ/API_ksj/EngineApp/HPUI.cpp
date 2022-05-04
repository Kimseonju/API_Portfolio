#include "HPUI.h"
#include <EngineRendererBasic.h>
#include <EngineWindowResMgr.h>
#include "Player.h"
//static
//static func


HPUI::HPUI()
{
}

HPUI::~HPUI()
{
}

void HPUI::Start()
{
	Player* player = LogicValue::MainPlayer;
	CCharacterInfo* info = player->GetCharacterInfo();
	//�÷��̾� HPMAX��ŭ �������ϱ�
	//��Ʈ���� HP������ �ٲٱ�
	//0 ���� 1 �ݺ� 2 ����
	int iHP=info->GetHP();
	int iHPMax=info->GetHPMax();


	for (int i = 0; i < iHPMax/2; ++i)
	{

		EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(1);
		//�� ��ĭ���� �ʱ�ȭ
		NewRenderer->TransCut_Setting(L"UI_hearts.bmp", 2);
		NewRenderer->SetPivotPos(float4(130.f+ (24.f*i), 35.f));

		NewRenderer->CamPosOff();
		NewRenderer->SetAlpha(200);
		m_MapRender.push_back(NewRenderer);
	}
	
}

void HPUI::Update()
{
	Player* player = LogicValue::MainPlayer;
	CCharacterInfo* info = player->GetCharacterInfo();
	int HP = info->GetHP();
	//2�� ���� ��Ʈ �ϳ�
	int HPMax = info->GetHPMax()/2;
	
	if (HPMax < m_MapRender.size())
	{
		int eraseRender = static_cast<int>(m_MapRender.size() - static_cast<int>(HPMax));
		//�ǳ� ����� ���ͽᵵ�ɰͰ��⵵�ѵ�
		for (int i = 0; i < eraseRender; ++i)
		{
			(*--(m_MapRender.end()))->Death();
			m_MapRender.erase(--(m_MapRender.end()));
		}
	}
	else if (HPMax > static_cast<int>(m_MapRender.size()))
	{
		for (int i = static_cast<int>(m_MapRender.size()); i < HPMax; ++i)
		{
			EngineRendererBasic* NewRenderer = CreateRenderer<EngineRendererBasic>(1);
			//�� ��ĭ���� �ʱ�ȭ
			NewRenderer->TransCut_Setting(L"UI_hearts.bmp", 2);
			NewRenderer->SetPivotPos(float4(130.f + (24.f * i), 35.f));

			NewRenderer->CamPosOff();
			NewRenderer->SetAlpha(200);
			m_MapRender.push_back(NewRenderer);
		}
	}
	std::list<EngineRendererBasic*>::iterator Start = m_MapRender.begin();
	std::list<EngineRendererBasic*>::iterator End = m_MapRender.end();
	for (; Start != End;++Start)
	{
		if (HP >= 2)
		{
			(*Start)->TransCut_Setting(L"UI_hearts.bmp", 0);
			(*Start)->SetAlpha(250);
			HP = HP - 2;
		}
		else if (HP >= 1) //����
		{
			(*Start)->TransCut_Setting(L"UI_hearts.bmp", 1);
			(*Start)->SetAlpha(250);
			HP = HP - 1;
		}
		else //ü�¾���
		{
			(*Start)->TransCut_Setting(L"UI_hearts.bmp", 2);
			(*Start)->SetAlpha(250);
		}
	}
}
