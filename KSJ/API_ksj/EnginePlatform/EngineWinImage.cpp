#include "EngineWinImage.h"
#include <EngineDebug.h>
#include "EngineWindow.h"

#pragma comment(lib, "msimg32.lib")

EngineWinImage::EngineWinImage() : m_BitMapInfo(), m_OldBitMap(nullptr),m_BitMap(0), m_DC(0), TransColor(RGB(255, 0, 255))
{
	m_Bland.AlphaFormat = AC_SRC_OVER;
	m_Bland.BlendFlags = 0;
	m_Bland.AlphaFormat = AC_SRC_ALPHA;
	m_Bland.SourceConstantAlpha = 255;
}

EngineWinImage::~EngineWinImage()
{
	if (nullptr != m_DC)
	{
		DeleteObject(m_BitMap);
		DeleteObject(m_OldBitMap);
		DeleteDC(m_DC);
	}
}
void EngineWinImage::Create(const Scale& _ImageScale)
{
	if (true == _ImageScale.IsZero2D())
	{
		EngineDebug::AssertMsg(L"if (true == _ImageScale.IsZero())");
	}
	m_BitMap = CreateCompatibleBitmap(EngineWindow::GetWindowDC(), _ImageScale.ix(), _ImageScale.iy());
	m_DC = CreateCompatibleDC(nullptr);
	if (nullptr == m_DC)
	{
		EngineDebug::AssertMsg(L"if (nullptr != m_DC)");
	}

	m_OldBitMap = (HBITMAP)SelectObject(m_DC, m_BitMap);
	ImageSizeCheck();

}

void EngineWinImage::Create(HDC _DC)
{
	if (nullptr == _DC)
	{
		EngineDebug::AssertMsg(L"if (nullptr == _DC)");
	}
	m_DC = _DC;
	ImageSizeCheck();
}

void EngineWinImage::ImageSizeCheck()
{
	HBITMAP CheckBitMap = (HBITMAP)GetCurrentObject(m_DC, OBJ_BITMAP);
	GetObjectW(CheckBitMap, sizeof(m_BitMapInfo), &m_BitMapInfo);
	m_Size.x = static_cast<float>(m_BitMapInfo.bmWidth);
	m_Size.y = static_cast<float>(m_BitMapInfo.bmHeight);
}

void EngineWinImage::Load(const EngineString& _LoadPath)
{
	m_BitMap = (HBITMAP)LoadImageW(nullptr,
		_LoadPath.c_str(), 
		IMAGE_BITMAP, 
		0, 
		0, 
		LR_LOADFROMFILE); 

	if (nullptr == m_BitMap)
	{
		EngineDebug::AssertMsg("if (nullptr == m_BitMap)");
	}

	m_DC = CreateCompatibleDC(nullptr);

	if (nullptr == m_DC)
	{
		EngineDebug::AssertMsg("if (nullptr != m_DC)");
	}

	m_OldBitMap = (HBITMAP)SelectObject(m_DC, m_BitMap);
	ImageSizeCheck();

}


void EngineWinImage::BitBlt(EngineWinImage& _OtherImage)
{
	// _OtherImage�̹����� �����ϴ� �׸��� 
	// this�̹����� �״�� (������)�������ִ� �Լ�
	BitBlt({ 0, 0 }, _OtherImage);
}


void EngineWinImage::BitBlt(float4 _Pos, EngineWinImage& _OtherImage)
{
	// :: �����Լ���°��� ������ش�.
	::BitBlt(m_DC,// ���� �̹����� �����ض�
		_Pos.ix(), // ���� �̹����� X0��������
		_Pos.iy(), // ���� �̹����� Y0��������
		_OtherImage.m_BitMapInfo.bmWidth,  // �̹����� �ʺ��
		_OtherImage.m_BitMapInfo.bmHeight, // �̹����� ���̸�ŭ
		_OtherImage.m_DC,
		0, // ���� �̹����� X0����
		0, // ���� �̹����� Y0����
		SRCCOPY); // ��� ����
}

void EngineWinImage::BitBltCenter(float4 _Pos, const float4& _Size, EngineWinImage& _OtherImage,
	const float4& _CutPos, const float4& _CutSize)
{
	::BitBlt(m_DC, _Pos.ix() - _Size.ihx(), // ���� �̹����� �׸����� �ϴ� ��ġ�� x
		_Pos.iy() - _Size.ihy(), // ���� �̹����� �׸����� �ϴ� ��ġ�� y
		_Size.ix(), // �׸����� �ϴ� ������ x
		_Size.iy(), // �׸����� �ϴ� ������ y
		_OtherImage.m_DC,
		_CutPos.ix(),
		_CutPos.iy(),
		SRCCOPY);
}

void EngineWinImage::TransparentBltCenter(const float4& _Pos, const float4& _Size, EngineWinImage& _OtherImage, 
	const float4& _CutPos, const float4& _CutSize)
{
	float4 CutSize = _CutSize;

	if (-1 == _CutSize.ix())
	{
		CutSize.x = static_cast<float>(_OtherImage.m_Size.ix());
	}

	if (-1 == _CutSize.iy())
	{
		CutSize.y = static_cast<float>(_OtherImage.m_Size.iy());
	}
	::TransparentBlt(m_DC,
		_Pos.ix() - _Size.ihx(), // ���� �̹����� �׸����� �ϴ� ��ġ�� x
		_Pos.iy() - _Size.ihy(), // ���� �̹����� �׸����� �ϴ� ��ġ�� y
		_Size.ix(), // �׸����� �ϴ� ������ x
		_Size.iy(), // �׸����� �ϴ� ������ y
		_OtherImage.m_DC,
		_CutPos.ix(),
		_CutPos.iy(),
		CutSize.ix(),
		CutSize.iy(),
		_OtherImage.TransColor); //�������


}


void EngineWinImage::TransparentBlt(const float4& _Pos, const float4& _Size, 
	EngineWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize)
{
	float4 CutSize = _CutSize;

	if (-1 == _CutSize.ix())
	{
		CutSize.x = static_cast<float>(_OtherImage.m_Size.ix());
	}

	if (-1 == _CutSize.iy())
	{
		CutSize.y = static_cast<float>(_OtherImage.m_Size.iy());
	}

	::TransparentBlt(m_DC,
		_Pos.ix(), // ���� �̹����� �׸����� �ϴ� ��ġ�� x
		_Pos.iy(), // ���� �̹����� �׸����� �ϴ� ��ġ�� y
		_Size.ix(), // �׸����� �ϴ� ������ x
		_Size.iy(), // �׸����� �ϴ� ������ y
		_OtherImage.m_DC,
		_CutPos.ix(),
		_CutPos.iy(),
		CutSize.ix(),
		CutSize.iy(),
		_OtherImage.TransColor); //�������


}


void EngineWinImage::AlphaBltCenter(const float4& _Pos, const float4& _Size, EngineWinImage& _OtherImage, const float4& _CutPos, const float4& _CutSize, BYTE _Alpha)
{

	m_Bland.SourceConstantAlpha = _Alpha;
	float4 CutSize = _CutSize;
	if (-1 == _CutSize.ix())
	{
		CutSize.x = static_cast<float>(_OtherImage.m_Size.ix());
	}

	if (-1 == _CutSize.iy())
	{
		CutSize.y = static_cast<float>(_OtherImage.m_Size.iy());
	}

	::AlphaBlend(m_DC,_Pos.ix() - _Size.ihx(), _Pos.iy() - _Size.ihy(), _Size.ix(), _Size.iy(), 
		_OtherImage.m_DC,_CutPos.ix(),_CutPos.iy(),CutSize.ix(),CutSize.iy(),m_Bland); 
}


void EngineWinImage::PlgBltCenter(const float4& _Pos, const float4& _Size, float _Angle, EngineWinImage& _OtherImage, EngineWinImage& _MaskImage)
{
	// ���� �׸��� ���� ��ġ
	float4 CenterPos = _Pos;

	float4 ArrRotPivot[3] = { {-_Size.hx(), -_Size.hy()}, {_Size.hx(), -_Size.hy()}, {-_Size.hx(), _Size.hy()} };

	for (size_t i = 0; i < 3; i++)
	{
		// �̰������� ȸ���� �༮�� �˴ϴ�.
		ArrRotPivot[i] = float4::AngleTo2DDeg(ArrRotPivot[i], _Angle);
	}

	// �� ������ ȸ�� ���Ѿ� �մϴ�.
	POINT ArrPos[3];

	for (size_t i = 0; i < 3; i++)
	{
		float4 Pos = ArrRotPivot[i] + CenterPos;

		ArrPos[i] = { Pos.ix(), Pos.iy() };
	}


	//  �̹��� ����� �Ǿ� �մϴ�.

	::PlgBlt(m_DC,
		ArrPos,
		_OtherImage.m_DC,
		0,
		0,
		_OtherImage.GetImageSize().ix(),
		_OtherImage.GetImageSize().iy(),
		_MaskImage.m_BitMap,
		0,
		0); // �������� ���� �����Ҳ���.

}



void EngineWinImage::ImageCut(int _X, int _Y)
{
	if (_X == 0 || _Y == 0)
	{
		EngineDebug::AssertMsg("if (_X == 0 || _Y == 0)");
	}

	float4 ImageSize = float4{ m_Size.ix() / _X, m_Size.iy() / _Y };
	float4 CurPos = float4{ 0,  0 };

	for (int y = 0; y < _Y; ++y)
	{
		for (int x = 0; x < _X; ++x)
		{
			m_CutData.push_back({ CurPos,ImageSize });
			CurPos.x += ImageSize.x;
		}
		CurPos.x = 0;
		CurPos.y += ImageSize.y;
	}
}

const CutData& EngineWinImage::GetCutData(int _Index)
{
	if (0 > _Index || m_CutData.size() <= _Index)
	{
		EngineDebug::AssertMsg("if (0 > _Index || m_CutData.size() <= _Index)");
	}
	return m_CutData[_Index];
}