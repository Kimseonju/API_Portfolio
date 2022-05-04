#pragma once
#include <EngineObjectBase.h>
#include <EngineMath.h>
#include "EngineActor.h"
// �з� : ������Ʈ
// �뵵 : ��������(Render), ���
// ���� : �������� ������ ũ�� �������ִ� ���Ͱ� �������� Ȯ���ϴ� Ŭ����
enum class RENDERINGMODE
{
    BIT,
    TRANS,
    TRANS_NOTCENTER,
    ROT,
    ALPHA,
    MAX,
};
class EngineActor;
class EngineWinImage;
class EngineRenderer : public EngineObjectBase
{
private: 
public: 
protected:
    EngineWinImage* m_MaskImage;
    RENDERINGMODE m_RenderingType;
    int m_Order;
    EngineActor* m_Actor;
    
    float4 m_RenderScale;
    float4 m_PivotPos;
    float4 m_CutPos;
    float4 m_CutSize;

    unsigned char m_Alpha;

    float m_Angle;
    int m_CutPoint;
    //������Ʈ�� ������ �׸����ʰ� �Ҽ��ִ� ����
    bool m_RenderOn;
public:
    //����ũ �̹��� ����
    void SetMaskImage(const EngineString& _Image);

    void SetAngle(float _Angle)
    {
        m_Angle = _Angle;

        if (0 != m_Angle)
        {
            m_RenderingType = RENDERINGMODE::ROT;
        }
    }

    void SetAlpha(unsigned char _Alpha)
    {
        m_Alpha = _Alpha;

        if (255 > _Alpha)
        {
            m_RenderingType = RENDERINGMODE::ALPHA;
        }
        
    }
    unsigned char GetAlpha()const
    {
        return m_Alpha;
    }
    float4 GetPivotPos() {
        return m_PivotPos;
    }

    void SetPivotPos(const float4& _PivotPos) {
        m_PivotPos = _PivotPos;
    }

    void SetPivotMove(const float4& _PivotPos) {
        m_PivotPos += _PivotPos;
    }

    float4 GetRenderScale() {
        return m_RenderScale;
    }

    void SetRenderScale(const float4& _RenderScale) {
        m_RenderScale = _RenderScale;
    } 
public:
    void SetOrder(int _Order)
    {
        m_Order = _Order;
    }

    int GetOrder()
    {
        return m_Order;
    }

    void SetActor(EngineActor* _Actor)
    {
        m_Actor = _Actor;
    }

    EngineActor* GetActor()
    {
        return m_Actor;
    }

    void RenderOff()
    {
        m_RenderOn = false;
    }
    void RenderOn()
    {
        m_RenderOn = true;
    }

    bool IsRender()
    {
        return m_RenderOn;
    }

   ////////////ķ�� 
private:
    bool m_IsCamPos;

public:
    // ķ�� ���� �޴��� �ȹ޴���.
    void CamPosOff()
    {
        m_IsCamPos = false;
    }

public:
    float4 CamRenderPos();

public:
    EngineRenderer();
    virtual ~EngineRenderer();

public: 
    EngineRenderer(const EngineRenderer& _Other) = delete;
    EngineRenderer(const EngineRenderer&& _Other) = delete;

public:
    EngineRenderer& operator=(const EngineRenderer& _Other) = delete;
    EngineRenderer& operator=(const EngineRenderer&& _Other) = delete;

public: 

    void RenderImage(EngineWinImage* _Image);

    //���� y���� ���� �ڵ� �Է�
    virtual void SetPositionYOrder() { m_Order = m_Actor->GetPosition().iy()+100; };
    virtual void Render() = 0;
};

