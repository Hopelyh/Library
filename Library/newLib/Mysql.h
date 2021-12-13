#pragma once
#include<iostream>
#include<string.h>
#include<cstring>
#include<string.h>
#include<vector>
#include<winsock.h>
#include<mysql.h>
#include<stdio.h>		//sprintf 与 sscanf 的头文件
#include<stdlib.h>
#include"User.h"
#include"Book.h"
#include"BorrowRecord.h"
#include"Time.h"
using namespace std;

class Mysql {
public:
	Mysql();
	~Mysql();

	bool OpenMysql();			//打开数据库声明
	bool CloseMysql();			//关闭数据库声明
			
	User ReadUser(string strUsername, string strUserPswd);

	bool AddUser(User user);		//新增用户函数
	bool AddBook(Book book);		//新增图书函数
	bool SelectAllBook(vector<Book>& books,int sum);
	bool QueryBookName(string strBookName,vector<Book> &books,int sum);
	bool QueryBookId(int bookid,Book &book);
	bool DeleteBookId(int bookid);
	bool AddBorrowRecord(BorrowRecord record);
	User QueryUserId(int userid);
	bool QueryAllRecord(vector<BorrowRecord>& borrowrecords,int sum);
	bool QueryUserRecord(vector<BorrowRecord> records,int userid,int sum);
	bool ReturnBook(int recordid, int bookid);
	bool QueryAllUser(vector<User> users,int sum);
	bool RenewBook(int recordid);
	bool QueryRecordId(BorrowRecord record, int recordid);

	//bool QueryUserRecordById(vector<BorrowRecord> records, int id);

public:
	string Username;		//用户名
	string Pswd;			//密码
	string Host;			//主机名
	string Database;		//数据库名
	int Port;				//端口号

	bool isOpen;			//打开标志
	MYSQL mysql;			//mysql连接
	MYSQL_RES* result;		//查询结果集
	MYSQL_ROW sql_row;		//一个行的列数组表示
	MYSQL_FIELD* fd;		//字段列数组

	Time newtime;
};
