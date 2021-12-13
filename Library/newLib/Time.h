#pragma once
#include<ctime>
#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>		//sprintf 与 sscanf的头文件
#include<cstdlib>
using namespace std;

class Time
{
public:
	Time() = default;
	~Time();

	void TimeToString(time_t time, char* ch);		//本地时间转string
	time_t StringToTime(char* ch);					//string 转本地时间
	string AddMonth(time_t& time1);					//续借图书，时间增加一个月


};