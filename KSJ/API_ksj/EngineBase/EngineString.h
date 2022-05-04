#pragma once

#include <string>
#include <vector>

// 분류 : 
// 용도 : 헬퍼 리소스
// 설명 : 프레임워크에서 문자열을 다루는 클래스
//        문자열에 대한 기능

class EngineString
{

private:
public: 
public: 
	std::wstring m_Str;

public: 

	EngineString();
	EngineString(const wchar_t* _pString);
	EngineString(const std::wstring& _String);
	~EngineString();
public:
    template<typename Type>
    static EngineString ToString(const Type& _Data)
    {
        EngineString String;
        String += EngineString(std::to_wstring(_Data));
        return String;
    }

	EngineString(const EngineString& _Other) : m_Str(_Other.m_Str){}
	EngineString(const EngineString&& _Other) noexcept : m_Str(_Other.m_Str){}

    EngineString(int _Other) noexcept : m_Str()
    {
        *this = ToString(_Other);
    }
public: 
    EngineString& operator=(const EngineString& _Other)
    {
        m_Str = _Other.m_Str;
        return *this;
    }
    EngineString& operator=(const EngineString&& _Other) noexcept
    {
        m_Str = _Other.m_Str;
        return *this;
    }

    EngineString& operator=(int _Value)
    {
        m_Str = std::to_wstring(_Value);
        return *this;
    }

    EngineString& operator=(float _Value)
    {
        m_Str = std::to_wstring(_Value);
        return *this;
    }
    EngineString operator+(const EngineString& _Other) const
    {
        std::wstring Str = m_Str;
        Str += _Other.m_Str;
        return Str;
    }


    EngineString& operator+=(const EngineString& _Other)
    {
        m_Str += _Other.m_Str;
        return *this;
    }

    bool operator!=(const EngineString& _Other) const
    {
        return m_Str != _Other.m_Str;
    }

    bool operator==(const EngineString& _Other) const
    {
        return m_Str == _Other.m_Str;
    }
    bool operator>(const EngineString& _Other) const
    {
        return m_Str > _Other.m_Str;
    }

    bool operator<(const EngineString& _Other) const
    {
        return m_Str < _Other.m_Str;
    }

    wchar_t& operator[](size_t _Index)
    {
        return m_Str[_Index];
    }





    size_t size() const {
        return m_Str.size();
    }

    void resize(size_t _Size) {
        return m_Str.resize(_Size);
    }

    void reserve(size_t _Size) {
        return m_Str.reserve(_Size);
    }

    const wchar_t* c_str() const
    {
        return m_Str.c_str();
    }

    std::vector<EngineString> StringCutVector(const wchar_t* _Pivot);
    std::vector<EngineString> StringCenterCutVector(const wchar_t* _Start, const wchar_t* _End);

    bool EraseFirst(const EngineString& _Str);
    bool EraseLast(const EngineString& _Str);
    void EraseAll(const EngineString& _Str);

public:
    std::string GetConvertMultiByte(int _encoding = 0) const;
    void SetConvertWideByte(const std::string& _Str);

    bool is_find(const wchar_t* _Text, size_t _StartIndex = 0);

    size_t find_first_index(const wchar_t* _Text, size_t _StartIndex = 0)const;
    size_t find_last_index(const wchar_t* _Text, size_t _EndIndex = -1)const;
    EngineString Cut(size_t _StartIndex, size_t _Count)const;
    EngineString CutIndex(size_t _StartIndex, size_t _EndIndex)const;
};

