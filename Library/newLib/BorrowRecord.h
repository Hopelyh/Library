#pragma once
#include<iostream>
#include<string>
//#include<time.h>
using namespace std;

class BorrowRecord 
{
 
public:
	BorrowRecord() = default;
	~BorrowRecord();

public:
	int r_id;					//记录ID
	int r_bookid;				//书籍ID
	int r_userid;				//用户ID
	string borrowdate;			//借出时间
	string shouldreturndate;	//归还期限时间
	string returndate;			//实际归还时间
	int re_bo_times;			//续借次数
};