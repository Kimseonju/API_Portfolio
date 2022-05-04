#include "EngineString.h"
#include <atlstr.h>

EngineString::EngineString()
{
}

EngineString::EngineString(const wchar_t* _pString) 
	: m_Str(_pString)
{
}

EngineString::EngineString(const std::wstring& _String) 
	: m_Str(_String)
{
}

EngineString::~EngineString()
{
}

std::vector<EngineString> EngineString::StringCutVector(const wchar_t* _Pivot)
{
	std::vector<EngineString> Return;

	EngineString PivotStr = _Pivot;

	size_t Start = 0;
	size_t End = find_first_index(_Pivot, Start);

	if (End == std::string::npos)
	{
		return Return;
	}

	while (true)
	{
		EngineString Text = CutIndex(Start, End);

		Return.push_back(Text);
		if (End == std::string::npos)
		{
			break;
		}


		Start = End + PivotStr.size();
		End = find_first_index(_Pivot, Start);


	}

	return Return;
}

std::vector<EngineString> EngineString::StringCenterCutVector(const wchar_t* _Start, const wchar_t* _End)
{
	std::vector<EngineString> Return;
	EngineString StartStr = _Start;
	EngineString EndStr = _End;

	size_t Start = find_first_index(StartStr.c_str(), 0);
	size_t End = find_first_index(EndStr.c_str(), Start + StartStr.size());

	if (Start == std::string::npos)
	{
		return Return;
	}

	while (true)
	{
		EngineString Text = CutIndex(Start + StartStr.size(), End);

		Return.push_back(Text);

		Start = find_first_index(StartStr.c_str(), End + EndStr.size());
		End = find_first_index(EndStr.c_str(), Start);

		if (Start == std::string::npos)
		{
			break;
		}
	}

	return Return;
}

bool EngineString::EraseFirst(const EngineString& _Str)
{
	size_t Index = find_first_index(_Str.c_str());

	if (Index == std::wstring::npos)
	{
		return false;
	}

	m_Str.erase(Index, _Str.size());

	return true;
}

bool EngineString::EraseLast(const EngineString& _Str)
{
	size_t Index = find_last_index(_Str.c_str());

	if (Index == std::wstring::npos)
	{
		return false;
	}

	m_Str.erase(Index, _Str.size());

	return true;
}

void EngineString::EraseAll(const EngineString& _Str)
{
	while (EraseFirst(_Str));
}

std::string EngineString::GetConvertMultiByte(int _encoding) const
{
	// wstring => string
	std::string Str = CW2A(m_Str.c_str(), _encoding).m_psz;
	return Str;
}

void EngineString::SetConvertWideByte(const std::string& _Str)
{
	// string => wstring
	m_Str = CA2W(_Str.c_str()).m_psz;
}

bool EngineString::is_find(const wchar_t* _Text, size_t _StartIndex)
{
	return std::wstring::npos != m_Str.find(_Text, _StartIndex);
}

size_t EngineString::find_first_index(const wchar_t* _Text, size_t _StartIndex)const
{
	return m_Str.find(_Text, _StartIndex);
}

size_t EngineString::find_last_index(const wchar_t* _Text, size_t _EndIndex)const
{
	return m_Str.rfind(_Text, _EndIndex);
}

EngineString EngineString::Cut(size_t _StartIndex, size_t _Count)const
{
	return m_Str.substr(_StartIndex, _Count);
}

EngineString EngineString::CutIndex(size_t _StartIndex, size_t _EndIndex)const
{
	return m_Str.substr(_StartIndex, _EndIndex - _StartIndex);
}
