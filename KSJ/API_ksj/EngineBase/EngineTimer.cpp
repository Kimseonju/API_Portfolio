#include "EngineTimer.h"

EngineTimer EngineTimer::MainTimer = EngineTimer();

double EngineTimer::GetDDeltaTime()
{
    return m_DDeltaTime;
}

float EngineTimer::GetFDeltaTime()
{
    return m_FDeltaTime;
}

void EngineTimer::Reset()
{
    QueryPerformanceCounter(&m_CurTime);
    QueryPerformanceCounter(&m_PrevTime);
}

void EngineTimer::CalTime()
{
    QueryPerformanceCounter(&m_CurTime);
    __int64 InterCount = m_CurTime.QuadPart - m_PrevTime.QuadPart;
    m_DDeltaTime = (double)InterCount / (double)m_CountTime.QuadPart;
    m_FDeltaTime = (float)m_DDeltaTime;
    m_PrevTime.QuadPart = m_CurTime.QuadPart;
}


EngineTimer::EngineTimer()
    : m_CountTime(), m_CurTime(), m_PrevTime(), m_DDeltaTime(), m_FDeltaTime()
{
    QueryPerformanceFrequency(&m_CountTime);

    Reset();
}