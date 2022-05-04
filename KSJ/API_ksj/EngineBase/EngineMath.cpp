#include "EngineMath.h"


const float4 float4::LEFT = { -1, 0 };
const float4 float4::RIGHT = { 1, 0 };
const float4 float4::UP = { 0 , -1 };
const float4 float4::DOWN = { 0 , 1 };
const float4 float4::AllDir[4] = { float4::LEFT ,float4::RIGHT ,float4::UP ,float4::DOWN };
const float4 float4::ZERO = { 0 , 0 };

//원주율값 알아서 자른다.
float EngineMath::FPI = 3.141592653589793238462643383279502884197169399375105820974944f;
double EngineMath::DPI = 3.141592653589793238462643383279502884197169399375105820974944;

//각도(60분법)  라디안(호도법)  
//180          = 3.14

//각도(60분법) -> 라디안(호도법)
float EngineMath::FD2R = FPI / 180;
// 라디안(호도법) ->각도(60분법)
float EngineMath::FR2D = 180 / FPI;

EngineMath::EngineMath()
{

}

EngineMath::~EngineMath()
{

}


Coliison2DCheck::StaticInst Coliison2DCheck::Inst;
bool (*Coliison2DCheck::ColFunc[static_cast<int>(COLTYPE::MAX)][static_cast<int>(COLTYPE::MAX)])(const Col2DData&, const Col2DData&);


void Coliison2DCheck::Init()
{
	//미리 함수포인터 정의해서 비교하지않고 바로실행
	//코드량이적다. ColFunc에 다 들어가있어서 하나의 함수만 쓰면된다(공통화)
	ColFunc[static_cast<int>(COLTYPE::RECT)][static_cast<int>(COLTYPE::RECT)] = RectToRect;
	ColFunc[static_cast<int>(COLTYPE::RECT)][static_cast<int>(COLTYPE::CIRCLE)] = RectToCirCle;
	ColFunc[static_cast<int>(COLTYPE::RECT)][static_cast<int>(COLTYPE::POINT)] = RectToPoint;
	ColFunc[static_cast<int>(COLTYPE::RECT)][static_cast<int>(COLTYPE::PIXEL)] = RectToPoint;
	
	ColFunc[static_cast<int>(COLTYPE::CIRCLE)][static_cast<int>(COLTYPE::RECT)] = CircleToRect;
	ColFunc[static_cast<int>(COLTYPE::CIRCLE)][static_cast<int>(COLTYPE::CIRCLE)] = CircleToCirCle;
	ColFunc[static_cast<int>(COLTYPE::CIRCLE)][static_cast<int>(COLTYPE::POINT)] = CircleToPoint;
	
	ColFunc[static_cast<int>(COLTYPE::POINT)][static_cast<int>(COLTYPE::RECT)] = PointToRect;
	ColFunc[static_cast<int>(COLTYPE::POINT)][static_cast<int>(COLTYPE::CIRCLE)] = PointToCirCle;
	ColFunc[static_cast<int>(COLTYPE::POINT)][static_cast<int>(COLTYPE::POINT)] = PointToPoint;

}

bool Coliison2DCheck::RectToRect(const Col2DData& _Left, const Col2DData& _Right)
{
	if (_Left.Right() < _Right.Left())
	{
		return false;
	}

	if (_Left.Left() > _Right.Right())
	{
		return false;
	}

	if (_Left.Up() > _Right.Down())
	{
		return false;
	}

	if (_Left.Down() < _Right.Up())
	{
		return false;
	}

	return true;
}
bool Coliison2DCheck::RectToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::RectToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::RectToPixel(const Col2DData& _Left, const Col2DData& _Right) 
{ 
	return true;
}

bool Coliison2DCheck::CircleToRect(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::CircleToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::CircleToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }

bool Coliison2DCheck::PointToRect(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::PointToCirCle(const Col2DData& _Left, const Col2DData& _Right) { return true; }
bool Coliison2DCheck::PointToPoint(const Col2DData& _Left, const Col2DData& _Right) { return true; }