#include<iostream>
//#include<string>
//#include<vector>
//#include<cstring>
//#include<winsock.h>
//#include<WinSock2.h>
//#pragma comment(lib,"wsock32.lib")
#include"User.h"
#include"Mysql.h"
#include"Book.h"
#include"Time.h"
#include"Manage.h"
#include"Student.h"

using namespace std;

int main()
{
	string strName, strPswd;
	Mysql new_mysql;
	new_mysql.OpenMysql();				//打开数据库
	User user;
	system("cls");
	//bool flag=true;
	cout << "请输入您的账号：" << endl;
	cin >> strName;
	cout << "请输入您的密码：" << endl;
	cin >> strPswd;
	user = new_mysql.ReadUser(strName, strPswd);
	while (user.Id == -1)
	{
		cout << "您输入的账号或密码有误，请重新输入,按任意键继续..." << endl;
		cin.get();
		cin.get();
		system("cls");
		cout << "请输入您的账号：" << endl;
		cin >> strName;
		cout << "请输入您的密码：" << endl;
		cin >> strPswd;
		user = new_mysql.ReadUser(strName, strPswd);
	}
	cout << "登入成功！" << endl;
	if (user.Role == 1)					//如果用户是管理员
	{
		bool flag = true;
		Manage manage;
		while (flag)
		{
			system("cls");
			manage.ShowMenu();
			cout << "请输入您的命令:" << endl;
			int chioce;
			cin >> chioce;
			switch (chioce)
			{
			case 1:
				manage.AddNewBook();
				break;
			case 2:
				manage.QueryBook();
				break;
			case 3:
				manage.ShowBookList();
				int bookid;
				cout << "请输入图书ID:" << endl;
				cin >> bookid;
				manage.DeleteBook(bookid);
				break;
			case 4:
				manage.ShowBookList();
				break;
			case 5:
				manage.ShowRecordList();
				break;
			case 6:
				manage.AddNewUser();
				break;
			case 7:
				manage.ShowUserList();
				break;
			case 0:
				new_mysql.CloseMysql();
				flag = false;
				break;
			default:
				break;
			}
		}
		cout << "您已退出登入，按任意键继续..." << endl;
	}
	else {								//如果用户是学生
		Student student;
		int command;
		bool flag = true;
		while (flag)
		{
			system("cls");
			student.ShowMenu();
			cout << "请输入您的命令：" << endl;
			cin >> command;
			switch (command)
			{
			case 1:
				student.QueryBook();
				break;
			case 2:
				student.BorrowBook(user.Id);
				break;
			case 3:
				student.ReturnBook(user.Id);
				break;
			case 4:
				student.QueryRecord(user.Id);
				break;
			case 5:
				student.RenewBook(user.Id);
				break;
			case 0:
				new_mysql.CloseMysql();
				flag = false;
			default:
				break;
			}
		}
		cout << "您已退出登入，按任意键继续..." << endl;
	}
	cin.get();
	cin.get();
	return 0;
}