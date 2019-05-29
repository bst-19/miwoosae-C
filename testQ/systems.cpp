#include "stdafx.h"
#include "systems.h"

wstring get_time() {

	SYSTEMTIME lst;
	GetLocalTime(&lst);

	wstringstream time_stream;

	wchar_t day[20];
	GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, 0, &lst, nullptr, day, 20, nullptr);
	
	time_stream << day;

	wchar_t time[20];
	GetTimeFormatEx(nullptr, 0, &lst, L"hh':'mm':'ss tt\n", time, 20);
	
	time_stream << " " << time;

	wcout << L"current time : " << day << L" " << time << endl;
	return time_stream.str();
}