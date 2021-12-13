#pragma once
#include<iostream>
#include<string.h>
#include<cstring>
#include<string.h>
#include<vector>
#include<winsock.h>
#include<mysql.h>
#include<stdio.h>		//sprintf �� sscanf ��ͷ�ļ�
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

	bool OpenMysql();			//�����ݿ�����
	bool CloseMysql();			//�ر����ݿ�����
			
	User ReadUser(string strUsername, string strUserPswd);

	bool AddUser(User user);		//�����û�����
	bool AddBook(Book book);		//����ͼ�麯��
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
	string Username;		//�û���
	string Pswd;			//����
	string Host;			//������
	string Database;		//���ݿ���
	int Port;				//�˿ں�

	bool isOpen;			//�򿪱�־
	MYSQL mysql;			//mysql����
	MYSQL_RES* result;		//��ѯ�����
	MYSQL_ROW sql_row;		//һ���е��������ʾ
	MYSQL_FIELD* fd;		//�ֶ�������

	Time newtime;
};
