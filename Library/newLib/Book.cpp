#include"Book.h"



Book::Book(int id, string name, string author, string pub, string isbn, time_t indate, int total, int left)
{
	BookId = id;					//ID
	BookName=name;			//书名
	BookAuthor=author;			//作者
	BookPub=pub;				//出版社
	BookISBN=isbn;			//图书ISBN	
	BookInDate=indate;			//入库日期
	BookTotal=total;				//总量
	BookLeft=left;				//余量
}

Book::~Book()
{

}

void Book::SetBookId(int id)
{
	BookId = id;
}

void Book::SetBookName(string name)
{
	BookName = name;
}

void Book::SetBookAuthor(string author)
{
	BookAuthor = author;
}

void Book::SetBookPub(string pub)
{
	BookPub = pub;
}

void Book::SetBookISBN(string isbn)
{
	BookISBN = isbn;
}

void Book::SetBookInDate(string inDate)
{
	BookInDate = inDate;
}

void Book::SetBookTotal(int total)
{
	BookTotal = total;
}

void Book::SetBookLeft(int left)
{
	BookLeft = left;
}


int Book::GetBookId()
{
	return BookId;
}

string Book::GetBookName()
{
	return BookName;
}

string Book::GetBookAuthor()
{
	return BookAuthor;
}

string Book::GetBookPub()
{
	return BookPub;
}

string Book::GetBookISBN()
{
	return BookISBN;
}

string Book::GetBookInDate()
{
	return BookInDate;
}

int Book::GetBookTotal()
{
	return BookTotal;
}

int Book::GetBookLeft()
{
	return BookLeft;
}