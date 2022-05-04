#pragma once
#include "EnginePath.h"
#include "EngineDebug.h"
#include <map>
class EngineFile : public EnginePath
{
private:
public: 
private:
    
    FILE* m_Handle;
    size_t m_FileSize;
    EngineString m_Mode;
    int m_CurMemoryPostion;

public:
    bool IsReadOpen() {
        return  m_Mode.is_find(L"r");
    }

    bool IsWriteOpen() {
        return  m_Mode.is_find(L"w");
    }

    size_t FileSize();
    size_t CurPostion();
public: 
    EngineFile();
    EngineFile(const EngineString& _Path);
    ~EngineFile();

public: 
    EngineFile(const EngineFile& _Other);
    EngineFile(const EngineFile&& _Other)  noexcept;

public: 
    EngineFile& operator=(const EngineFile& _Other) = delete;
    EngineFile& operator=(const EngineFile&& _Other) = delete;

public: 
    void Open(const wchar_t* _Mode);
    void Close();

public:
    template<typename T>
    void operator << (T& _Value)
    {
        Write(&_Value, sizeof(_Value), 1);
    }

    template<>
    void operator << (const EngineString& _Value)
    {
        // wideByte변환
        std::string Convert = _Value.GetConvertMultiByte();
        //문자열사이즈 저장
        int Size = static_cast<int>(Convert.size());
        Write(&Size, sizeof(int), 1);
        //멀티바이트로 바꿔서 저장.
        Write((void*)Convert.c_str(), Size, 1);
    }

    template<>
    void operator<<(EngineString& _Value)
    {
        const EngineString& constString = _Value;
        operator<<(constString);
    }


    template <typename KEY, typename VALUE>
    void operator << (std::map<KEY, VALUE> _Value)
    {
        //사이즈저장
        int Size = _Value.size();
        Write(&Size, sizeof(int), 1);

        typename std::map<KEY, VALUE>::iterator iter = _Value.begin();;
        typename std::map<KEY, VALUE>::iterator iterEnd = _Value.end();;

        for (; iter != iterEnd; ++iter)
        {
            const KEY first = iter->first;
            *this << first;
            VALUE second = iter->second;
            *this << second;
        }
    }
    template<typename T>
    void WriteType(T& _Value, size_t _Count = 1)
    {
        Write(&_Value, sizeof(_Value), _Count);
    }

    void Write(void* _Ptr, size_t _Size, size_t _Count = 1);


public:
    template<typename T>
    void operator >> (T& _Value)
    {
        Read(&_Value, sizeof(_Value), sizeof(_Value), 1);
    }
    template<>
    void operator >> (EngineString& _Value)
    {
        //사이즈읽기
        int Size = 0;
        Read(&Size, sizeof(int), sizeof(int),  1);

        //사이즈가없다..?!
        if (0 >= Size)
        {
            EngineDebug::AssertMsg(L"Read Size if (0 >= Size)");
        }

        std::string ReadBuffer;
        ReadBuffer.resize(Size);

        Read(&ReadBuffer[0], Size, Size, 1);
        _Value.SetConvertWideByte(ReadBuffer);
    }

    template <typename KEY, typename VALUE>
    void operator >> (std::map<KEY, VALUE>& _Value)
    {

        int Size = 0;
        this->operator>>(Size);

        typename std::map<KEY, VALUE>::iterator iter = _Value.begin();;
        typename std::map<KEY, VALUE>::iterator iterEnd = _Value.end();;
        for (size_t i = 0; i < Size; ++i)
        {
            KEY mapkey;
            *this >> mapkey;
            VALUE value;
            *this >> value;
            _Value.insert(std::map<KEY, VALUE>::value_type(mapkey, value));
        }
    }

    template<typename T>
    void ReadType(T& _Value, size_t _Count = 1)
    {
        Read(&_Value, sizeof(_Value), sizeof(_Value), _Count);
    }

    void Read(void* _Ptr, size_t _BufferSize, size_t _ReadSize, size_t _Count = 1);
};

