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
	int r_id;					//��¼ID
	int r_bookid;				//�鼮ID
	int r_userid;				//�û�ID
	string borrowdate;			//���ʱ��
	string shouldreturndate;	//�黹����ʱ��
	string returndate;			//ʵ�ʹ黹ʱ��
	int re_bo_times;			//�������
};