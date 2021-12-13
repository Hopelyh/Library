#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include<stdlib.h>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<ctype.h>
#include<time.h>


#include"Book.h"
#include"BorrowRecord.h"
#include"Mysql.h"
#include"User.h"
#include"Time.h"
using namespace std;

class Student
{
public:
	Student() = default;
	~Student();

	bool ShowMenu();
	bool QueryBook();
	bool BorrowBook(int userid);
	bool ReturnBook(int userid);
	bool QueryRecord(int userid);
	bool RenewBook(int userid);

private:
	Mysql new_mysql;
	Time new_time;
};


#endif // !_STUDENT_H
