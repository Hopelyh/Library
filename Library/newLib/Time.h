#pragma once
#include<ctime>
#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>		//sprintf �� sscanf��ͷ�ļ�
#include<cstdlib>
using namespace std;

class Time
{
public:
	Time() = default;
	~Time();

	void TimeToString(time_t time, char* ch);		//����ʱ��תstring
	time_t StringToTime(char* ch);					//string ת����ʱ��
	string AddMonth(time_t& time1);					//����ͼ�飬ʱ������һ����


};