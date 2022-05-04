#include "EngineDirectory.h"
#include <Windows.h>
#include "EngineDebug.h"
#include "EngineFile.h"
#include <io.h>

EngineString EngineDirectory::GetCurrentDirectoryPath()
{
	wchar_t Arr[512] = { 0 };

	GetCurrentDirectoryW(MAX_PATH, Arr);

	EngineString ReturnPath = Arr;
	ReturnPath += L"\\";

	return ReturnPath;
}

void EngineDirectory::GetCurrentDirectoryPath(EngineString& _String)
{
	_String = GetCurrentDirectoryPath();
}

EngineDirectory::EngineDirectory() 
	: EnginePath(GetCurrentDirectoryPath())
{
}

EngineDirectory::~EngineDirectory()
{

}

EngineString EngineDirectory::DirectoryName()
{
	return IOName();
}

void EngineDirectory::MoveParent(const EngineString& _DirName) {

	while (DirectoryName() != _DirName)
	{
		MoveParent();
	}
}

void EngineDirectory::MoveParent()
{
	size_t LastIndex = find_last_index(L"\\", size() - 2);
	EngineString::operator=(CutIndex(0, LastIndex + 1));
}

void EngineDirectory::MoveChild(const EngineString& _Path)
{
	EngineString::operator+=(_Path + L"\\");

	if (false == IsExist())
	{
		EngineDebug::AssertMsg(_Path + L"if (false == IsExist())");
	}
}

std::vector<EngineFile> EngineDirectory::DirectoryAllFileToVector(const EngineString& _CheckPath)
{
	std::vector<EngineFile> ReturnVector;
	_wfinddata64i32_t fd;
	EngineString Path = c_str();

	Path += _CheckPath;
	intptr_t FindHandle = _wfindfirst(Path.c_str(), &fd);

	if (-1 == FindHandle)
	{
		EngineDebug::AssertMsg(L"if (-1 == HANDLE)");
	}

	do
	{
		if (fd.attrib & _A_SUBDIR)
		{
			_wfindnext(FindHandle, &fd);
			continue;
		}

		EngineString FileName = fd.name;
		EngineFile NewFile = operator+(FileName);

		ReturnVector.push_back(NewFile);
	} while (0 == _wfindnext(FindHandle, &fd));

	_findclose(FindHandle);

	return ReturnVector;
}