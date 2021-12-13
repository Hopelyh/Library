#include"Student.h"
Student::~Student()
{

}

//菜单展示
bool Student::ShowMenu()
{
	system("cls");
	cout << "==========================欢迎使用图书馆后台管理系统：==========================" << endl;
	cout << "                              1.查询图书" << endl;
	cout << "                              2.借阅图书" << endl;
	cout << "                              3.归还图书" << endl;
	cout << "                              4.借阅记录" << endl;
	cout << "                              5.续借图书" << endl;
	cout << "                              0.退出登录" << endl;
	return true;
}

//根据书名查询
bool Student::QueryBook()
{
	string name;
	cout << "请输入书名:" << endl;
	cin >> name;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	vector<Book>books;
	int sum=-1;
	new_mysql.QueryBookName(name, books, sum);				//返回查询
	vector<Book>::iterator vecIter;
	cout << "共查询到：" << sum << " 条结果";
	cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//借阅图书
bool Student::BorrowBook(int userid)
{
	QueryBook();
	int id;
	cout << "请输入你想要借阅的书籍ID:" << endl;
	cin.get();
	cin >> id;
	Book book;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	new_mysql.QueryBookId(id, book);
	if (book.GetBookLeft() > 0)
	{
		cout << "请问是否要借阅本书：(y/n)" << endl;
		char ch;
		while (cin >> ch)
		{
			if (ch == 'Y' || ch == 'y')
			{
				BorrowRecord new_record;
				new_record.r_bookid = id;
				new_record.r_id = userid;
				time_t time1;
				time1 = time(NULL);
				char ch[16] = { 0 };
				new_time.TimeToString(time1, ch);					//日历时间转time
				new_record.shouldreturndate = new_time.AddMonth(time1);
				new_record.returndate = "";
				new_record.re_bo_times = 0;
				book.SetBookLeft(book.GetBookLeft() - 1);
				new_mysql.AddBorrowRecord(new_record);
				//cout << "借阅成功" << endl;
				break;
			}
			else if (ch == 'n' || ch == 'N')
			{
				cout << "已取消！" << endl;
				break;
			}
			else {
				cout << "输入错误，请重新输入" << endl;
				cin.get();
				continue;
			}
		}

	}
	else {
		cout << "该书籍已经全部借出，无法借阅！" << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//归还图书
bool Student::ReturnBook(int userid)
{
	vector<BorrowRecord>records;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	int sum=-1;
	new_mysql.QueryUserRecord(records, userid,sum);
	Book book;
	cout << "查询到您的借阅信息如下,共 "<<sum<<" 条" << endl;
	cout << "ID		书名			出版社			借阅时间			应还时间			续借次数" << endl;
	vector<BorrowRecord>::iterator vecIter = records.begin();
	for (; vecIter != records.end(); vecIter++)
	{
		new_mysql.QueryBookId(vecIter->r_bookid, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->r_id << "   " << setw(14) << book.GetBookName() << "   " << setw(14) << book.GetBookPub()
			<< "   " << setw(14) << vecIter->borrowdate << "   " << setw(14) << vecIter->shouldreturndate << "   " << setw(10) << vecIter->re_bo_times;
				
	}
	int re_id;
	cout << "请输入您要归还的图书借阅记录ID：" << endl;
	while (cin >> re_id)
	{
		for (;vecIter!=records.end();vecIter++)
		{
			if (vecIter->r_id == re_id)
			{
				break;
			}
		}
		if (vecIter == records.end())
		{
			cout << "您输入的ID不在记录中，请重新输入：" << endl;
		}
	}
	new_mysql.ReturnBook(re_id, vecIter->r_bookid);
	cout << "还书成功！" << endl;
	cin.get();
	cin.get();
	return true;	
}

//借阅记录
bool Student::QueryRecord(int userid)
{
	Book book;
	int sum=-1;
	vector<BorrowRecord>records;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	new_mysql.QueryUserRecord(records, userid,sum);
	cout << "查询到您的借阅信息 " << sum << " 条：" << endl; 
	cout << "ID		书名			出版社			借阅时间			应还时间			续借次数" << endl;
	vector<BorrowRecord>::iterator vecIter = records.begin();
	for (; vecIter != records.end(); vecIter++)
	{
		new_mysql.QueryBookId(vecIter->r_bookid, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->r_id << "   " << setw(14) << book.GetBookName() << "   " << setw(14) << book.GetBookPub()
			<< "   " << setw(14) << vecIter->borrowdate << "   " << setw(14) << vecIter->shouldreturndate << "   " << setw(10) << vecIter->re_bo_times;
	}
	cin.get();
	cin.get();
	return true;
}

//续借图书
bool Student::RenewBook(int userid)
{
	Book book;
	int sum=-1;
	int re_id;
	vector<BorrowRecord>records;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	new_mysql.QueryUserRecord(records, userid, sum);
	cout << "查询到您的借阅信息 " << sum << " 条：" << endl;
	cout << "ID		书名			出版社			借阅时间			应还时间			续借次数" << endl;
	vector<BorrowRecord>::iterator vecIter = records.begin();
	for (; vecIter != records.end(); vecIter++)
	{
		new_mysql.QueryBookId(vecIter->r_bookid, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->r_id << "   " << setw(14) << book.GetBookName() << "   " << setw(14) << book.GetBookPub()
			<< "   " << setw(14) << vecIter->borrowdate << "   " << setw(14) << vecIter->shouldreturndate << "   " << setw(10) << vecIter->re_bo_times;
	}
	cout << "请输入您要续借的图书借阅记录ID：" << endl;
	while (cin >> re_id)
	{
		for (; vecIter != records.end(); vecIter++)
		{
			if (vecIter->r_id == re_id)
			{
				break;
			}
		}
		if (vecIter == records.end())
		{
			cout << "您输入的ID不在记录中，请重新输入：" << endl;
		}
	}
	new_mysql.RenewBook(re_id);
	cout << "续借成功!" << endl;
	cin.get();
	cin.get();
	return true;
}