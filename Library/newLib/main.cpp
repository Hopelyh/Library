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
	new_mysql.OpenMysql();				//�����ݿ�
	User user;
	system("cls");
	//bool flag=true;
	cout << "�����������˺ţ�" << endl;
	cin >> strName;
	cout << "�������������룺" << endl;
	cin >> strPswd;
	user = new_mysql.ReadUser(strName, strPswd);
	while (user.Id == -1)
	{
		cout << "��������˺Ż�������������������,�����������..." << endl;
		cin.get();
		cin.get();
		system("cls");
		cout << "�����������˺ţ�" << endl;
		cin >> strName;
		cout << "�������������룺" << endl;
		cin >> strPswd;
		user = new_mysql.ReadUser(strName, strPswd);
	}
	cout << "����ɹ���" << endl;
	if (user.Role == 1)					//����û��ǹ���Ա
	{
		bool flag = true;
		Manage manage;
		while (flag)
		{
			system("cls");
			manage.ShowMenu();
			cout << "��������������:" << endl;
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
				cout << "������ͼ��ID:" << endl;
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
		cout << "�����˳����룬�����������..." << endl;
	}
	else {								//����û���ѧ��
		Student student;
		int command;
		bool flag = true;
		while (flag)
		{
			system("cls");
			student.ShowMenu();
			cout << "�������������" << endl;
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
		cout << "�����˳����룬�����������..." << endl;
	}
	cin.get();
	cin.get();
	return 0;
}