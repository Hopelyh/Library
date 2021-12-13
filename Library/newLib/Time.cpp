#include"Time.h"

Time::~Time()
{

}

void Time::TimeToString(time_t time, char* ch)
{
	struct tm* ti;
	ti = localtime(&time);
	sprintf(ch, "%4.4d-%2.2d-%2.2d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday);
}

//字符串转换为time_t类型
time_t Time::StringToTime(char* ch)
{
	struct tm ti;
	time_t time1 = NULL;
	sscanf_s(ch, "%4d%2d%2d%2d%2d%2d",
		&ti.tm_year,
		&ti.tm_mon,
		&ti.tm_mday,
		&ti.tm_hour,
		&ti.tm_min,
		&ti.tm_sec);
	ti.tm_year -= 1900;
	ti.tm_mon -= 1;
	ti.tm_mday = -1;
	time1 = mktime(&ti);
	return time1;
}

//续借图书，借阅日期增加
string Time::AddMonth(time_t &time1)
{
	struct tm* ti;
	ti = localtime(&time1);
	switch (ti->tm_mon++)
	{
	case 1:
		if (ti->tm_mday== 29)
		{
			if ((ti->tm_year + 1900) / 4 == 0 && (ti->tm_year + 1900) / 100 != 0 || (ti->tm_year + 1900) / 400 == 0)
			{
				//ti->tm_mday++;
				ti->tm_mon++;
				break;
			}
			else {
				ti->tm_mon++;
				ti->tm_mday=28;
				break;
			}
		}
		else if(ti->tm_mday>29) {
			ti->tm_mon++;
			ti->tm_mday = 28;
		}
		else {
			ti->tm_mon++;
		}
		break;
	case 2:
	case 4:
	case 6:
	case 9:
	case 11:
		ti->tm_mon++;
		break;
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
		if (ti->tm_mday == 31)
		{
			ti->tm_mday = 30;
			ti->tm_mon++;
		}
		else {
			ti->tm_mon++;
		}
		break;
	case 12:
		ti->tm_year++;
		ti->tm_mon = 1;
	default:
		break;
	}
	char newtime[16];
	sprintf(newtime, "%4.4d-%2.2d-%2.2d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday);
	return newtime;
}

