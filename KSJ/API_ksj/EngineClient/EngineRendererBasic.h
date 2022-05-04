#pragma once
#include "EngineRenderer.h"
#include <EngineWinImage.h>
#include <EngineDebug.h>

class EngineRendererBasic : public EngineRenderer
{
private:
public: 
private:

    EngineWinImage* m_Image;
public:
    void SetCutData(int _Index)
    {
        if (nullptr == m_Image)
        {
            EngineDebug::AssertMsg("if (nullptr == m_Image)");
        }
        const CutData& Data = m_Image->GetCutData(_Index);
        m_CutPos = Data.m_Pos;
        m_CutSize = Data.m_Size;
    }
    
    void SetCutPosAndSize(const float4& _Pos, const float4& _Size)
    {
        m_CutPos = _Pos;
        m_CutSize = _Size;
    }


    float4 GetCutPos()
    {
        return m_CutPos;
    }
    void SetCutPos(const float4& _Pos)
    {
        m_CutPos = _Pos;
    }

    float4 GetCutSize()
    {
        return m_CutSize;
    }
    void SetCutSize(const float4& _Size)
    {
        m_CutSize = _Size;
    }
public:
    void TransCut_NotCenterSetting(const EngineString& _ImageName, int _Start);
    void TransCut_Setting(const EngineString& _ImageName, int _Start);
    void BltCut_Setting(const EngineString& _ImageName, int _Start);

    void TransSetting(const EngineString& _Image, float4 _Scale, float4 _PivotPos = float4{ 0,0 }, int _TransRgb = RGB(255, 0, 255));
    void TransNotCenter();


    void RotImageSetting(const EngineString& _Image, const EngineString& _MaskImage, float4 _Scale, float4 _PivotPos = float4{ 0,0 });

public: 
    EngineRendererBasic();
    ~EngineRendererBasic();

public: 
    EngineRendererBasic(const EngineRendererBasic& _Other) = delete;
    EngineRendererBasic(const EngineRendererBasic&& _Other) = delete;

public: 
    EngineRendererBasic& operator=(const EngineRendererBasic& _Other) = delete;
    EngineRendererBasic& operator=(const EngineRendererBasic&& _Other) = delete;

public:
    void Render() override;
};

