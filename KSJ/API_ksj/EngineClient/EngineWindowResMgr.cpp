#include "EngineWindowResMgr.h"
#include <EnginePath.h>
#include <EngineDebug.h>

EngineWindowResMgr::EngineWindowResMgr()
{

}

EngineWindowResMgr::~EngineWindowResMgr()
{
	Release();
}

void EngineWindowResMgr::Release() {
	std::map<EngineString, EngineWinImage*>::iterator Start = m_Image.begin();
	std::map<EngineString, EngineWinImage*>::iterator End = m_Image.end();
	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			delete Start->second;
			Start->second = nullptr;
		}
	}

	m_Image.clear();
}

EngineWinImage* EngineWindowResMgr::FindImage(const EngineString& _Name)
{
	if (m_Image.end() == m_Image.find(_Name))
	{
		return nullptr;
	}

	return m_Image[_Name];
}
void EngineWindowResMgr::ImageLoad(const EngineString& _Path)
{
	EngineString FileName = EnginePath::IOName(_Path);

	if (nullptr != FindImage(FileName))
	{
		EngineDebug::AssertMsg("if (nullptr != FindImage(FileName))");
		return;
	}

	EngineWinImage* NewImage = new EngineWinImage();
	NewImage->Load(_Path);
	m_Image.insert(std::map<EngineString, EngineWinImage*>::value_type(FileName, NewImage));
}