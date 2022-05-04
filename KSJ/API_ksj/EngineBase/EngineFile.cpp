#include "EngineFile.h"
#include "EngineDebug.h"

EngineFile::EngineFile() 
	: m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
{
}

EngineFile::EngineFile(const EngineString& _Path) 
	: EnginePath(_Path)
	, m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
{
}

EngineFile::EngineFile(const EngineFile& _Other) : EnginePath(_Other.m_Str), m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
{

}

EngineFile::EngineFile(const EngineFile&& _Other) noexcept : EnginePath(_Other.m_Str), m_Handle(nullptr), m_CurMemoryPostion(0), m_FileSize(0)
{

}

EngineFile::~EngineFile()
{
	Close();
}

void EngineFile::Close()
{

	if (nullptr != m_Handle)
	{
		fclose(m_Handle);
		m_Handle = nullptr;
	}
}

void EngineFile::Open(const wchar_t* _Mode)
{
	//열려있다면 닫고시작
	Close();
	m_Mode = _Mode;

	m_CurMemoryPostion = 0;
	//권한에따라 파일열기
	_wfopen_s(&m_Handle, c_str(), m_Mode.c_str());

	if (nullptr == m_Handle)
	{
		EngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}

	fseek(m_Handle, 0, SEEK_END);
	m_FileSize = ftell(m_Handle);
	fseek(m_Handle, 0, SEEK_SET);
}

void EngineFile::Write(void* _Ptr, size_t _Size, size_t _Count)
{
	if (nullptr == m_Handle)
	{
		EngineDebug::AssertMsg(L"if (nullptr == m_Handle)");
	}

#ifdef _DEBUG
	if (true == IsReadOpen())
	{
		EngineDebug::AssertMsg(L"if (true == IsReadOpen())");
	}
#endif
	fwrite(_Ptr, _Size, _Count, m_Handle);
}

void EngineFile::Read(void* _Ptr, size_t _BufferSize, size_t _ReadSize, size_t _Count /*= 1*/)
{
	fread_s(_Ptr, _BufferSize, _ReadSize, _Count, m_Handle);
}

size_t EngineFile::FileSize()
{
	if (nullptr == m_Handle)
	{
		return m_FileSize;
	}
	return m_FileSize;

}


size_t EngineFile::CurPostion()
{
	return ftell(m_Handle);
}