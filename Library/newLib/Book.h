#ifndef _BOOK_H
#define _BOOK_H


#pragma once
#include<string>
#include<ctime>
//#include<iostream>
using namespace std;

class Book {
public:
	Book()=default;
	Book(int id, string name, string author, string pub, string isbn, time_t indate, int total, int left);
	void SetBookId(int id);
	int GetBookId();
	void SetBookName(string name);
	void SetBookAuthor(string author);
	void SetBookPub(string pub);
	void SetBookISBN(string isbn);
	void SetBookInDate(string inDate);
	void SetBookTotal(int total);
	void SetBookLeft(int letf);
	string GetBookName();
	string GetBookAuthor();
	string GetBookPub();
	string GetBookISBN();
	string GetBookInDate();
	int GetBookTotal();
	int GetBookLeft();
	~Book();

private:
	int BookId;						//ID
	string BookName;			//����
	string BookAuthor;			//����
	string BookPub;				//������
	string BookISBN;			//ͼ��ISBN	
	string BookInDate;			//�������
	int BookTotal;				//����
	int BookLeft;				//����
};

#endif // !1
