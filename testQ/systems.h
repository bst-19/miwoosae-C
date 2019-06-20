#pragma once
#pragma warning(disable:4996)


#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>


using namespace std;

wstring get_lst(void);
wstring get_time(void);
wstring get_date(void);
chrono::steady_clock::time_point get_nano_time();
wstring timepoint_to_wstring(const std::chrono::system_clock::time_point& p_tpTime, const std::string& p_sFormat);