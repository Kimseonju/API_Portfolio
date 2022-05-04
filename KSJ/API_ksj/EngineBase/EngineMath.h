#pragma once
#include <math.h>
#include <random>
class EngineMath
{
private:
public: 
    static float FPI;
    static double DPI;

    static float FD2R;
    static float FR2D;
private:

private: 
    EngineMath();
    ~EngineMath();

private: 
    EngineMath(const EngineMath& _Other) = delete;
    EngineMath(const EngineMath&& _Other) = delete;

public: 
    EngineMath& operator=(const EngineMath& _Other) = delete;
    EngineMath& operator=(const EngineMath&& _Other) = delete;

public:
};

class float4
{
public:
    static const float4 LEFT;
    static const float4 RIGHT;
    static const float4 UP;
    static const float4 DOWN;
    static const float4 AllDir[4];
    static const float4 ZERO;
public:
    static float4 AngleToDir2DDeg(float _Deg)
    {
        return AngleToDir2DRad(_Deg * EngineMath::FD2R);
    }

    static float4 AngleToDir2DRad(float _Rad)
    {
        //sinf > 높이 / 빗변 -> y구하기
        //cosf > 밑변/빗변 -> x구하기

        float4 Return;
        Return.x = cosf(_Rad); //밑변
        Return.y = sinf(_Rad); //높이
        return Return;
    }
    static float RadianToDegree(float fRadian)
    {
        return fRadian * 180.f / EngineMath::FPI;
    }
    static float GetAngle(float4 _This, float4 _Other)
    {

        float4 vec = _This - _Other;
        vec.Normalize();
        float rad = atan2f(vec.y, vec.x);
        float Angle = float4::RadianToDegree(rad);
        if (Angle < 0.f)
            Angle += 360.f;
        return Angle;
    }
    static float GetAngle(float4 _This)
    {

        float4 vec = _This;
        vec.Normalize();
        float rad = atan2f(vec.y, vec.x);
        float Angle = float4::RadianToDegree(rad);
        if (Angle < 0.f)
            Angle += 360.f;
        return Angle;
    }

    static float GetRendomAngle()
    {
        std::random_device rd;
        std::mt19937_64 rng1(rd());
        std::uniform_int_distribution<int> dist(0, 360);

        return static_cast<float>(dist(rng1));
    }
    static float4 GetRandomAngleRad()
    {
        std::random_device rd;
        std::mt19937_64 rng1(rd());
        std::uniform_int_distribution<int> dist(0, 360);
        float angle=static_cast<float>(dist(rng1));

        float4 Return=AngleToDir2DDeg(angle);
        return Return;
    }
    //{0,0}을 기준으로 회전해주는 함수
    static float4 AngleTo2DDeg(const float4& _Ori, float _Deg)
    {
        return AngleTo2DRad(_Ori, _Deg * EngineMath::FD2R);
    }

    static float4 AngleTo2DRad(const float4& _Ori, float _Rad)
    {
        float4 Return;

        Return.x = (cosf(_Rad) * _Ori.x) - (sinf(_Rad) * _Ori.y);
        Return.y = (sinf(_Rad) * _Ori.x) + (cosf(_Rad) * _Ori.y);
        return Return;
    }




    //길이(빗변) 반환하는 함수
    static float Len2D(const float4& _Value)
    {
        return sqrtf((_Value.x * _Value.x) + (_Value.y * _Value.y));
    }

    static float Len3D(const float4& _Value)
    {
        return sqrtf((_Value.x * _Value.x) + (_Value.y * _Value.y)+ (_Value.z * _Value.z));
    }

    static float LenXZ(const float4& _Value)
    {
        return sqrtf((_Value.y * _Value.y) + (_Value.z * _Value.z));
    }
    //단위벡터 반환하는 함수
    static float4 Normalize2D(const float4& _Value)
    {
        float4 ReturnValue = _Value;
        float Len = Len2D(_Value);
        if (Len == 0.f)
            return float4::ZERO;
        ReturnValue.x = _Value.x / Len;
        ReturnValue.y = _Value.y / Len;
        ReturnValue.z = 0.0f;
        return ReturnValue;
    }

    //단위벡터 반환하는 함수
    static float4 Normalize3D(const float4& _Value)
    {
        float4 ReturnValue = _Value;
        float Len = Len3D(_Value);
        ReturnValue.x = _Value.x / Len;
        ReturnValue.y = _Value.y / Len;
        ReturnValue.z = _Value.z / Len;
        return ReturnValue;
    }

    static float4 NormalizeXZ(const float4& _Value)
    {
        float4 ReturnValue = _Value;
        float Len = LenXZ(_Value);
        ReturnValue.x = _Value.x / Len;
        ReturnValue.y = _Value.y / Len;
        ReturnValue.z = _Value.z / Len;
        return ReturnValue;
    }

    void Normalize()
    {
        *this = Normalize2D(*this);
    }

    float Len()
    {
        return Len2D(*this);

    }
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        struct
        {
             float r;
             float g;
             float b;
             float a;
        };
    };
    float4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
    {
    }

    float4(
        float _value
    ) : x(_value), y(_value), z(_value), w(_value)
    {
    }

    float4(
        float _x, float _y
    ) : x(_x), y(_y), z(0.0f), w(1.0f)
    {
    }

    float4(
        float _x, float _y, float _z
    ) : x(_x), y(_y), z(_z), w(1.0f)
    {
    }

    float4(float _x, float _y, float _z, float _w
    ) : x(_x), y(_y), z(_z), w(_w)
    {
    }
    float4(int _value)
        :x(static_cast<float>(_value)), y(static_cast<float>(_value)), z(static_cast<float>(_value)), w(static_cast<float>(_value))
    {
    }

    float4(int _x, int _y)
        :x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(0.0f), w(1.0f)
    {
    }
    float4(int _x, int _y, int _z)
        :x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(1.0f)
    {
    }
    float4(int _x, int _y, int _z, int _w)
        :x(static_cast<float>(_x)), y(static_cast<float>(_y)), z(static_cast<float>(_z)), w(static_cast<float>(_w))
    {
    }

public:

    static float4 Lerp2DMax(float4 _Start, float4 _End, float _Ratio)
    {
        if (0 >= _Ratio)
        {
            _Ratio = 0.0f;
        }

        if (1.0f <= _Ratio)
        {
            _Ratio = 1.0f;
        }

        return Lerp2D(_Start, _End, _Ratio);
    }

    static float4 Lerp2D(float4 _Start, float4 _End, float _Ratio)
    {
        float4 ReturnValue;
        ReturnValue.x = (1 - _Ratio) * _Start.x + _Ratio * _End.x;
        ReturnValue.y = (1 - _Ratio) * _Start.y + _Ratio * _End.y;

        return ReturnValue;
    }

    bool IsZero2D() const
    {
        return x == 0 || y == 0;
    }
    bool IsZero()const
    {
        return x == 0 || y == 0 || z == 0;
    }
    int ix() const
    {
        return static_cast<int>(x);
    }
    int iy() const
    {
        return static_cast<int>(y);
    }
    int iz() const
    {
        return static_cast<int>(z);
    }
    int iw() const
    {
        return static_cast<int>(w);
    }
    int ihx() const
    {
        return static_cast<int>(x * 0.5f);
    }
    int ihy()const
    {
        return static_cast<int>(y * 0.5f);
    }
    int ihz()const
    {
        return static_cast<int>(z * 0.5f);
    }
    int ihw()const
    {
        return static_cast<int>(w * 0.5f);
    }

    float hx()const
    {
        return x * 0.5f;
    }
    float hy()const
    {
        return y * 0.5f;
    }
    float hz()const
    {
        return z * 0.5f;
    }
    float hw()const
    {
        return w * 0.5f;
    }

    float4 hfloat4()const
    {
        return { hx(), hy() };
    }

    float4 operator+(const float4& _Other)
    {
        float4 ReturnVector;
        ReturnVector.x = x + _Other.x;
        ReturnVector.y = y + _Other.y;
        ReturnVector.z = z + _Other.z;
        ReturnVector.w = w + _Other.w;
        return ReturnVector;
    }

    float4 operator*(const float& _Value) const
    {
        float4 ReturnVector;
        ReturnVector.x = x * _Value;
        ReturnVector.y = y * _Value;
        ReturnVector.z = z * _Value;
        ReturnVector.w = w * _Value;
        return ReturnVector;
    }

    float4 operator-(const float4& _Other) const
    {
        float4 ReturnVector;
        ReturnVector.x = x - _Other.x;
        ReturnVector.y = y - _Other.y;
        ReturnVector.z = z - _Other.z;
        ReturnVector.w = w - _Other.w;
        return ReturnVector;
    }

    float4 operator-() const
    {
        float4 ReturnVector;
        ReturnVector.x = -x  ;
        ReturnVector.y = -y  ;
        ReturnVector.z = -z  ;
        ReturnVector.w = -w  ;
        return ReturnVector;
    }

    float4 operator+(const float4& _Other) const
    {
        float4 ReturnVector;
        ReturnVector.x = x + _Other.x;
        ReturnVector.y = y + _Other.y;
        ReturnVector.z = z + _Other.z;
        ReturnVector.w = w + _Other.w;
        return ReturnVector;
    }

    float4& operator+=(const float4& _Other)
    {
        x += _Other.x;
        y += _Other.y;
        z += _Other.z;
        w += _Other.w;
        return *this;
    }
    float4& operator-=(const float4& _Other)
    {
        x -= _Other.x;
        y -= _Other.y;
        z -= _Other.z;
        w -= _Other.w;
        return *this;
    }
    bool operator==(const float4& _Other) const
    {
        return x==_Other.x && y==_Other.y;
    }

    bool operator!=(const float4& _Other) const
    {
        return x != _Other.x || y != _Other.y;
    }
};


typedef float4 Vector;
typedef float4 Position;
typedef float4 Scale;
typedef float4 FRect;
typedef float4 Color;


//collision

enum class COLTYPE
{
    RECT,
    CIRCLE,
    POINT,
    PIXEL,
    MAX,
};


class Col2DData
{
public: 
    float4 Pos;
    float4 Size;
    float Left() const
    {
        return Pos.x - Size.hx();
    }
    float Right()const {
        return Pos.x + Size.hx();
    }
    float Up()const {
        return Pos.y - Size.hy();
    }
    float Down()const
    {
        return Pos.y + Size.hy();
    }

    int iLeft() const
    {
        return static_cast<int>(Left());
    }
    int iRight()const {
        return static_cast<int>(Right());
    }
    int iUp()const {
        return static_cast<int>(Up());
    }
    int iDown()const
    {
        return static_cast<int>(Down());
    }

    //float4 LeftPoint() const
    //{
    //    return { Pos.y, Left() };
    //}
    //float4 RightPoint()const {
    //    return { Pos.y, Right() };
    //}
    //float4 UpPoint()const {
    //    return { Pos.x, Up() };
    //}
    //float4 DownPoint()const
    //{
    //    return { Pos.x, Down() };
    //}

};

class Coliison2DCheck
{
public:
    static bool (*ColFunc[static_cast<int>(COLTYPE::MAX)][static_cast<int>(COLTYPE::MAX)])(const Col2DData&, const Col2DData&);

private:
    class StaticInst
    {
        friend Coliison2DCheck;
    private:
        //클래스 Inst변수가 전역변수라서 선언되면 자동으로 실행이된다.
        //장점은 따로 선언하지않아도 실행이된다
        //단점은 이와 비슷한 방식을 실행할때
        //순서를 정할수가없다 (순서정해야하는거면 안됨)
        StaticInst()
        {
            Coliison2DCheck::Init();
        }
        ~StaticInst() {

        }
    };

    friend StaticInst;
    //데이터(static)가 만들어진다.
    static StaticInst Inst;

private:
    static void Init();

public:
    static bool RectToRect(const Col2DData& _Left, const Col2DData& _Right);
    static bool RectToCirCle(const Col2DData& _Left, const Col2DData& _Right);
    static bool RectToPoint(const Col2DData& _Left, const Col2DData& _Right);
    static bool RectToPixel(const Col2DData& _Left, const Col2DData& _Right);

    static bool CircleToRect(const Col2DData& _Left, const Col2DData& _Right);
    static bool CircleToCirCle(const Col2DData& _Left, const Col2DData& _Right);
    static bool CircleToPoint(const Col2DData& _Left, const Col2DData& _Right);

    static bool PointToRect(const Col2DData& _Left, const Col2DData& _Right);
    static bool PointToCirCle(const Col2DData& _Left, const Col2DData& _Right);
    static bool PointToPoint(const Col2DData& _Left, const Col2DData& _Right);

private:
    virtual ~Coliison2DCheck();
};