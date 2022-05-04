#include "EngineInput.h"
#include <Windows.h>


std::map<EngineString, EngineInput::EngineKey> EngineInput::m_KeyMap;

EngineInput::EngineKey::EngineKey()
	: Down(false), Press(false), Up(false), Free(true)
{

}

EngineInput::EngineKey::~EngineKey()
{

}

bool EngineInput::EngineKey::KeyCheck()
{
	for (size_t i = 0; i < m_Key.size(); i++)
	{
		if (0 == GetAsyncKeyState(m_Key[i]))
		{
			return false;
		}
	}
	return true;
}

void EngineInput::EngineKey::Reset()
{
	Down = false;
	Press = false;
	Up = false;
	Free = true;
}

void EngineInput::EngineKey::Update()
{
	if (true == KeyCheck())
	{
		if (true == Free) //안눌러져있었다면
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else //이미누른상태라면
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}

	}
	else
	{

		if (true == Press) //눌렀다 땐상태
		{
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else //땐상태
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}


	}
}


EngineInput::EngineInput()
{

}

EngineInput::~EngineInput()
{

}

EngineInput::EngineKey& EngineInput::FindKey(const EngineString& _Name)
{
	if (m_KeyMap.end() == m_KeyMap.find(_Name))
	{
		EngineDebug::AssertMsg("if (m_KeyMap.end() == m_KeyMap.find(_Name))");
		return m_KeyMap[_Name];
	}
	return m_KeyMap[_Name];
}

void EngineInput::Update()
{
	std::map<EngineString, EngineKey>::iterator Start = m_KeyMap.begin();
	std::map<EngineString, EngineKey>::iterator End = m_KeyMap.end();

	for (; Start != End; ++Start)
	{
		Start->second.Update();
	}
}

bool EngineInput::IsFree(const EngineString& _Name)
{
	return FindKey(_Name).Free;
}
bool EngineInput::IsUp(const EngineString& _Name)
{
	return FindKey(_Name).Up;
}
bool EngineInput::IsPress(const EngineString& _Name)
{
	return FindKey(_Name).Press;
}
bool EngineInput::IsDown(const EngineString& _Name)
{
	return FindKey(_Name).Down;
}

void EngineInput::KeyReset()
{
	std::map<EngineString, EngineKey>::iterator Start = m_KeyMap.begin();
	std::map<EngineString, EngineKey>::iterator End = m_KeyMap.end();

	for (; Start != End; ++Start)
	{
		Start->second.Reset();
	}
}
