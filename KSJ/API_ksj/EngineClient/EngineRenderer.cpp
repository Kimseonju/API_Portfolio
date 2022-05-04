#include "EngineRenderer.h"
#include <EngineWindow.h>
#include <EngineWinImage.h>
#include "EngineWindowResMgr.h"

EngineRenderer::EngineRenderer() :
	m_IsCamPos(true),
	m_RenderingType(RENDERINGMODE::MAX),
	m_CutPos(),
	m_CutSize(-1, -1),
	m_Actor(nullptr),
	m_Order(0),
	m_CutPoint(-1),
	m_Alpha(0),
	m_MaskImage(nullptr),
	m_Angle(0.f),
	m_RenderScale(float4::ZERO),
	m_PivotPos(float4::ZERO),
	m_RenderOn(true)
	
{
}
EngineRenderer::~EngineRenderer()
{
}


float4 EngineRenderer::CamRenderPos()
{
	if (true == m_IsCamPos)
	{
		return GetActor()->GetPosition() + m_PivotPos - GetActor()->GetScene()->GetCamPos();
	}

	return GetActor()->GetPosition() + m_PivotPos;
}

void EngineRenderer::RenderImage(EngineWinImage* _Image)
{
	switch (m_RenderingType)
	{
	case RENDERINGMODE::BIT:
		if (-1 != m_CutPoint)
		{
			const CutData& _Data = _Image->GetCutData(m_CutPoint);
			if (m_RenderScale != float4::ZERO)
			{
				EngineWindow::GetBackBufferImage().BitBltCenter(CamRenderPos(), m_RenderScale, *_Image, _Data.m_Pos, _Data.m_Size);
			}
			else
				EngineWindow::GetBackBufferImage().BitBltCenter(CamRenderPos(), _Data.m_Size, *_Image, _Data.m_Pos, _Data.m_Size);
		}
		else
		{
			EngineWindow::GetBackBufferImage().BitBltCenter(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize);
		}

		break;
	case RENDERINGMODE::TRANS:
		if (-1 != m_CutPoint)
		{
			const CutData& _Data = _Image->GetCutData(m_CutPoint);
			if (m_RenderScale != float4::ZERO)
			{
				EngineWindow::GetBackBufferImage().TransparentBltCenter(CamRenderPos(), m_RenderScale, *_Image, _Data.m_Pos, _Data.m_Size);
			}
			else
				EngineWindow::GetBackBufferImage().TransparentBltCenter(CamRenderPos(), _Data.m_Size, *_Image, _Data.m_Pos, _Data.m_Size);
		}
		else
		{
			EngineWindow::GetBackBufferImage().TransparentBltCenter(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize);
		}
		break;
	case RENDERINGMODE::TRANS_NOTCENTER:
		if (-1 != m_CutPoint)
		{
			const CutData& _Data = _Image->GetCutData(m_CutPoint);
			if (m_RenderScale == float4::ZERO)
			{
				EngineWindow::GetBackBufferImage().TransparentBlt(CamRenderPos(), _Data.m_Size, *_Image, _Data.m_Pos, _Data.m_Size);

			}
			else
			{
				EngineWindow::GetBackBufferImage().TransparentBlt(CamRenderPos(), m_RenderScale, *_Image, _Data.m_Pos, _Data.m_Size);
			}
			
		}
		else
		{
			EngineWindow::GetBackBufferImage().TransparentBlt(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize);
		}
		
		break;
	case RENDERINGMODE::ROT:
		EngineWindow::GetBackBufferImage().PlgBltCenter(CamRenderPos(), m_RenderScale, m_Angle, *_Image, *m_MaskImage);
		break;
	case RENDERINGMODE::ALPHA:
		if (-1 != m_CutPoint)
		{
			const CutData& _Data = _Image->GetCutData(m_CutPoint);
			if (m_RenderScale == float4::ZERO)
			{
				EngineWindow::GetBackBufferImage().AlphaBltCenter(CamRenderPos(), _Data.m_Size, *_Image, _Data.m_Pos, _Data.m_Size, m_Alpha);

			}
			else
			{
				EngineWindow::GetBackBufferImage().AlphaBltCenter(CamRenderPos(), m_RenderScale, *_Image, _Data.m_Pos, _Data.m_Size, m_Alpha);
			}

		}
		else
		{
			EngineWindow::GetBackBufferImage().AlphaBltCenter(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize, m_Alpha);
		}

		break;
	case RENDERINGMODE::MAX:
	default:
		EngineDebug::AssertMsg("case RENDERINGMODE::MAX:");
		break;
	}
}

void EngineRenderer::SetMaskImage(const EngineString& _Image)
{
	m_MaskImage = EngineWindowResMgr::Inst().FindImage(_Image);

	if (nullptr == m_MaskImage)
	{
		EngineDebug::AssertMsg("if (nullptr == m_Image)");
	}

}