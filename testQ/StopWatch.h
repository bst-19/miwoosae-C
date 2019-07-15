#pragma once
#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__
#include <sys/timeb.h>


class STOPWATCH
{
private:
	struct _timeb m_Stb;
	struct _timeb m_Etb;
	struct _timeb m_Mtb;
	__int64 m_stime;
	__int64 m_etime;
	__int64 m_ttime;
public:
	void Start()
	{
		_ftime(&m_Stb);
	}
	void End()
	{
		_ftime(&m_Etb);
	}
	__int64 TimeCheck()
	{
		m_stime = (__int64)m_Stb.time * (1000) + (__int64)m_Stb.millitm;
		m_etime = (__int64)m_Etb.time * (1000) + (__int64)m_Etb.millitm;
		return (m_etime - m_stime);
	}
	__int64 mTimeCheck()
	{
		_ftime(&m_Mtb);
		m_stime = (__int64)m_Stb.time * (1000) + (__int64)m_Stb.millitm;
		m_ttime = (__int64)m_Mtb.time * (1000) + (__int64)m_Mtb.millitm;
		return (m_ttime - m_stime);
	}
};

#endif