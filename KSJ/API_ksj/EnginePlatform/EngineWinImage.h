#pragma once
#include <Windows.h>
#include <EngineMath.h>
#include <EngineString.h>
class CutData
{
public:
    float4 m_Pos;
    float4 m_Size;
};
class EngineWinImage
{
private:
public: 
private:
    HDC m_DC;
    HBITMAP m_BitMap;
    HBITMAP m_OldBitMap;
    BITMAP m_BitMapInfo;

    float4 m_Size;
    int TransColor;
    BLENDFUNCTION m_Bland;

public:
    float4 GetImageSize()
    {
        return m_Size;
    }

    void SetTransColor(int _Color)
    {
        TransColor = _Color;
    }

    unsigned long GetPixelColor(int _X, int _Y)
    {
        return GetPixel(m_DC, _X, _Y);
    }
private:
    std::vector<CutData> m_CutData;

public:
    int GetCutSize()
    {
        return static_cast<int>(m_CutData.size());
    }
    float4 GetSize()
    {
        return m_Size;
    }
    const CutData& GetCutData(int _Index);
    void ImageCut(int _X, int _Y);

public:
    HDC ImageDC()
    {
        return m_DC;
    }

public: 
    EngineWinImage();
    ~EngineWinImage();

public: 
    EngineWinImage(const EngineWinImage& _Other) = delete;
    EngineWinImage(const EngineWinImage&& _Other) = delete;

public:
    EngineWinImage& operator=(const EngineWinImage& _Other) = delete;
    EngineWinImage& operator=(const EngineWinImage&& _Other) = delete;

private:
    void ImageSizeCheck();

public: 
    void Create(const Scale& _ImageScale);
    void Create(HDC _DC);
    void Load(const EngineString& _LoadPath);

public:
    void BitBlt(EngineWinImage& _OtherImage);
    void BitBlt(float4 _Pos, EngineWinImage& _OtherImage);
    void BitBltCenter(float4 _Pos, const float4& _Size, EngineWinImage& _OtherImage,
        const float4& _CutPos, const float4& _CutSize);


public:
    void TransparentBlt(const float4& _Pos, const float4& _Size, EngineWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize);
    void TransparentBltCenter(const float4& _Pos, const float4& _Size, EngineWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize);
    void TransparentBltBottom(const float4& _Pos, const float4& _Size, EngineWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize);
public:
    void AlphaBltCenter(const float4& _Pos, const float4& _Size, EngineWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize, BYTE _Alpha);
    
public:
    // È¸Àü
    void PlgBltCenter(const float4& _Pos, const float4& _Size, float _Angle, EngineWinImage& _OtherImage, EngineWinImage& _MaskImage);
};