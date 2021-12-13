#pragma once
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctype.h>
#include <time.h>

#include"Mysql.h"
#include"Time.h"
#include"Book.h"
#include"User.h"
using namespace std;

class Manage
{
public:
	Manage() = default;
	~Manage();

	void ShowMenu();
	bool AddNewBook();
	bool QueryBook();
	bool DeleteBook(int bookid);
	bool ShowBookList();
	bool ShowRecordList();
	bool AddNewUser();
	bool ShowUserList();


public:
	Mysql new_mysql;
	Time te_time;
};