#include "EnginePath.h"

bool EnginePath::IsExist(const EngineString& _Path)
{
	return 0 == _waccess(_Path.c_str(), 00);
}

bool EnginePath::IsExist()
{
	return IsExist(m_Str.c_str());
}

EnginePath::EnginePath()
{
}

EnginePath::EnginePath(const EngineString& _Path) 
	: EngineString(_Path)
{
}

EnginePath::~EnginePath()
{
}
