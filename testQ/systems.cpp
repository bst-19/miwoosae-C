#include "stdafx.h"
#include "systems.h"

wstring get_lst() {

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

wstring get_date() {

	wchar_t *lst = (wchar_t *)malloc(sizeof(wchar_t) * wcslen(get_lst().c_str()));
	wcscpy(lst, get_lst().c_str());

	wchar_t *ptr = wcstok(lst, L" ");

	return ptr;
}

wstring get_time() {
	wchar_t *lst = (wchar_t *)malloc(sizeof(wchar_t) * wcslen(get_lst().c_str()));
	wcscpy(lst, get_lst().c_str());

	wchar_t *ptr = wcstok(lst, L" ");
	ptr = wcstok(NULL, L" ");

	return ptr;
}

chrono::steady_clock::time_point get_nano_time(){
	auto cur_nano = chrono::high_resolution_clock::now();
	return cur_nano;
}


wstring timepoint_to_wstring(const std::chrono::system_clock::time_point& p_tpTime, const std::string& p_sFormat)
{
	auto converted_timep = std::chrono::system_clock::to_time_t(p_tpTime);
	ostringstream oss;
	oss << std::put_time(std::localtime(&converted_timep), p_sFormat.c_str());

	wstringstream w_oss;
	w_oss << oss.str().c_str();
	return w_oss.str();
}
