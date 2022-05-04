#include "EngineRendererBasic.h"
#include "EngineWindowResMgr.h"
#include <EngineDebug.h>
#include <EngineWindow.h>

EngineRendererBasic::EngineRendererBasic() : m_Image(nullptr)
{

}

EngineRendererBasic::~EngineRendererBasic()
{

}
void EngineRendererBasic::Render()
{
	if (m_RenderOn)
	{
		RenderImage(m_Image);
	}
	
}

void EngineRendererBasic::TransCut_NotCenterSetting(const EngineString& _ImageName, int _Start)
{
	m_Image = EngineWindowResMgr::Inst().FindImage(_ImageName);
	if (NULL == m_Image)
	{
		EngineDebug::AssertMsg("if (nullptr == FindImage)");
	}
	if (0 >= m_Image->GetCutSize())
	{
		EngineDebug::AssertMsg("if (0 >= FindImage->GetCurSize())");
	}
	if (0 > _Start || _Start >= m_Image->GetCutSize())
	{
		EngineDebug::AssertMsg("_Start _End Error");
	}
	m_CutPoint = _Start;
	m_RenderingType = RENDERINGMODE::TRANS_NOTCENTER;
}

void EngineRendererBasic::TransCut_Setting(const EngineString& _ImageName, int _Start)
{
	m_Image = EngineWindowResMgr::Inst().FindImage(_ImageName);
	if (NULL == m_Image)
	{
		EngineDebug::AssertMsg("if (nullptr == FindImage)");
	}
	if (0 >= m_Image->GetCutSize())
	{
		EngineDebug::AssertMsg("if (0 >= FindImage->GetCurSize())");
	}
	if (0 > _Start || _Start >= m_Image->GetCutSize())
	{
		EngineDebug::AssertMsg("_Start _End Error");
	}
	m_CutPoint = _Start;
	m_RenderingType = RENDERINGMODE::TRANS;
}

void EngineRendererBasic::BltCut_Setting(const EngineString& _ImageName, int _Start)
{
	m_Image = EngineWindowResMgr::Inst().FindImage(_ImageName);
	if (NULL == m_Image)
	{
		EngineDebug::AssertMsg("if (nullptr == FindImage)");
	}
	if (0 >= m_Image->GetCutSize())
	{
		EngineDebug::AssertMsg("if (0 >= FindImage->GetCurSize())");
	}
	if (0 > _Start || _Start >= m_Image->GetCutSize())
	{
		EngineDebug::AssertMsg("_Start _End Error");
	}
	m_CutPoint = _Start;
	m_RenderingType = RENDERINGMODE::BIT;
}

void EngineRendererBasic::TransSetting(const EngineString& _Image, float4 _Scale, float4 _PivotPos, int _TransRgb)
{
	m_Image = EngineWindowResMgr::Inst().FindImage(_Image);

	if (NULL == m_Image)
	{
		EngineDebug::AssertMsg("if (nullptr == m_Image)");
	}
	m_PivotPos = _PivotPos;
	m_RenderScale = _Scale;
	m_RenderingType = RENDERINGMODE::TRANS;
}

void EngineRendererBasic::TransNotCenter()
{
	m_RenderingType = RENDERINGMODE::TRANS_NOTCENTER;
}
void EngineRendererBasic::RotImageSetting(const EngineString& _Image, const EngineString& _MaskImage, float4 _Scale, float4 _PivotPos /*= float4{ 0,0 }*/)
{
	TransSetting(_Image, _Scale, _PivotPos);
	SetMaskImage(_MaskImage);
}