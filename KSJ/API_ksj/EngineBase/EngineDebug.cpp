#include "EngineDebug.h"
#include <assert.h>
#include <Windows.h>


void EngineDebug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(13828);
}

void EngineDebug::AssertMsg(const EngineString& _ErrorMsg)
{
#ifdef _DEBUG
	assert(! _ErrorMsg.c_str());
#endif
	// 
}
void EngineDebug::AssertMsg(const std::string& _ErrorMsg) 
{
#ifdef _DEBUG
	assert(! _ErrorMsg.c_str());
#endif
}


void EngineDebug::OutPutMsg(const EngineString& _ErrorMsg)
{
	OutputDebugStringW(_ErrorMsg.c_str());
}
EngineDebug::EngineDebug()
{

}

EngineDebug::~EngineDebug()
{

}