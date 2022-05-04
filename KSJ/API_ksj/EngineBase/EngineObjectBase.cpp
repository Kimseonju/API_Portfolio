#include "EngineObjectBase.h"
//static
//static func


EngineObjectBase::EngineObjectBase():
	m_IsOn(true), m_IsDeath(false), m_Parent(nullptr), m_IsOnTask(false), m_IsOffTask(false)
{
}

EngineObjectBase::~EngineObjectBase()
{
}
