#include"Manage.h"

Manage::~Manage()
{

}

//管理员菜单
void Manage::ShowMenu()
{
	system("cls");
	cout << "==========================欢迎使用图书馆后台管理系统：==========================" << endl;
	cout << "                              1.新书录入" << endl;
	cout << "                              2.图书查询" << endl;
	cout << "                              3.删除图书" << endl;
	cout << "                              4.图书列表" << endl;
	cout << "                              5.借阅记录" << endl;
	cout << "                              6.新增用户" << endl;
	cout << "                              7.用户列表" << endl;
	cout << "                              0.退出登录" << endl;
}

//新书录入
bool Manage::AddNewBook()
{
	string name, author, pub, isbn;
	int total;
	time_t indate = time(NULL);
	char ch[16] = { 0 };
	te_time.TimeToString(indate, ch);
	cout << "请按下列顺序依次输入书籍信息：" << endl;
	cout << "书名			作者			出版社		ISBN		总量" << endl;
	cin >> name;
	cin >> author;
	cin >> pub;
	cin >> isbn;
	cin >> total;

	Book book;
	book.SetBookName(name);
	book.SetBookAuthor(author);
	book.SetBookPub(pub);
	book.SetBookISBN(isbn);
	book.SetBookInDate(ch);
	book.SetBookTotal(total);
	
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	new_mysql.AddBook(book);
	cout << "新增图书成功！" << endl;
	cin.get();
	
	return true;
}

//图书查询
bool Manage::QueryBook()
{
	string name;
	cout << "请输入书名：" << endl;
	cin >> name;
	Book book;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	vector<Book> books;
	int sum=-1;
	new_mysql.QueryBookName(name, books,sum);
	cout << "共查询到 " << sum << " 条结果" << endl;
	vector<Book>::iterator vecIter;
	cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//删除图书
bool Manage::DeleteBook(int bookid)
{
	Book book;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	new_mysql.QueryBookId(bookid, book);
	if (book.GetBookId() != -1)
	{
		cout << "查询到如下结果:" << endl;
		Book *vecIter = &book;
		cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
		cout << "是否确定删除（y/n)" << endl;
		cin.get();
		char ch;
		while (cin >> ch)
		{
			if (ch == 'Y' || ch == 'y')
			{
				new_mysql.DeleteBookId(bookid);
				break;
			}
			else if (ch == 'N' || ch == 'n') {
				cout << "已取消删除！" << endl;
				break;
			}
			else {
				cout << "输入有误，请重新输入！" << endl;
			}
		}
	}
	else {
		cout << "没有找到ID为：" << bookid << "的书籍" << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//展示图书列表
bool Manage::ShowBookList()
{
	vector<Book> books;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	int sum=0;
	new_mysql.SelectAllBook(books,sum);
	cout << "共查询到 " << sum << " 条结果：" << endl;
	vector<Book>::iterator vecIter;
	cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
	}
	return true;
}

//展示借阅记录
bool Manage::ShowRecordList()
{
	vector<BorrowRecord>records;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	int sum = 0;
	Book book;
	User user;
	new_mysql.QueryAllRecord(records, sum);
	cout << "共查询到 " << sum << " 条结果：" << endl;
	cout << "ID     书名            借阅人           借阅日期       应还日期        实还日期		续借次数" << endl;
	vector<BorrowRecord>::iterator vecIter;
	for (vecIter = records.begin(); vecIter != records.end(); vecIter++)
	{
		new_mysql.QueryBookId(vecIter->r_bookid, book);
		user=new_mysql.QueryUserId(vecIter->r_userid);
		cout << setiosflags(ios::left) << setw(4) << vecIter->r_id << "  " << setw(14) << book.GetBookName() << "  " << setw(10) << user.strName << "  " << setw(14) << vecIter->borrowdate << "  " << setw(14) << vecIter->shouldreturndate << "  " << setw(8) << vecIter->returndate << "  " << setw(3) << vecIter->re_bo_times << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//新增用户
bool Manage::AddNewUser()
{
	string name, passwd;
	//int role;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	cout << "请输入用户信息：" << endl;
	cout << "用户名		密码			类型" << endl;
	User user;
	cin >> user.strName;
	cin >> user.strPassword;
	cin >> user.Role;
	new_mysql.AddUser(user);
	cout << "新增用户成功" << endl;
	cin.get();
	cin.get();
	return true;
}

//展示用户列表
bool Manage::ShowUserList()
{
	vector<User>users;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	int sum=-1;
	new_mysql.QueryAllUser(users,sum);
	cout << "共查询到：" << sum << " 条结果" << endl;
	vector<User>::iterator vecIter;
	cout << "ID     用户名      身份" << endl;
	for (vecIter = users.begin(); vecIter != users.end(); vecIter++)
	{
		cout << setiosflags(ios::left) << setw(6) << vecIter->Id << "  " << setw(8) << vecIter->strName << "  " << (vecIter->Role == 1 ? "管理员" : "学生") << endl;
	}
	cin.get();
	cin.get();
	return true;
}