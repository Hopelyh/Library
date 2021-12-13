#include"Manage.h"

Manage::~Manage()
{

}

//����Ա�˵�
void Manage::ShowMenu()
{
	system("cls");
	cout << "==========================��ӭʹ��ͼ��ݺ�̨����ϵͳ��==========================" << endl;
	cout << "                              1.����¼��" << endl;
	cout << "                              2.ͼ���ѯ" << endl;
	cout << "                              3.ɾ��ͼ��" << endl;
	cout << "                              4.ͼ���б�" << endl;
	cout << "                              5.���ļ�¼" << endl;
	cout << "                              6.�����û�" << endl;
	cout << "                              7.�û��б�" << endl;
	cout << "                              0.�˳���¼" << endl;
}

//����¼��
bool Manage::AddNewBook()
{
	string name, author, pub, isbn;
	int total;
	time_t indate = time(NULL);
	char ch[16] = { 0 };
	te_time.TimeToString(indate, ch);
	cout << "�밴����˳�����������鼮��Ϣ��" << endl;
	cout << "����			����			������		ISBN		����" << endl;
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
	cout << "����ͼ��ɹ���" << endl;
	cin.get();
	
	return true;
}

//ͼ���ѯ
bool Manage::QueryBook()
{
	string name;
	cout << "������������" << endl;
	cin >> name;
	Book book;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	vector<Book> books;
	int sum=-1;
	new_mysql.QueryBookName(name, books,sum);
	cout << "����ѯ�� " << sum << " �����" << endl;
	vector<Book>::iterator vecIter;
	cout << "ID     ����            ����           ������       �������     �ݲ�����   ����" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//ɾ��ͼ��
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
		cout << "��ѯ�����½��:" << endl;
		Book *vecIter = &book;
		cout << "ID     ����            ����           ������       �������     �ݲ�����   ����" << endl;
		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
		cout << "�Ƿ�ȷ��ɾ����y/n)" << endl;
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
				cout << "��ȡ��ɾ����" << endl;
				break;
			}
			else {
				cout << "�����������������룡" << endl;
			}
		}
	}
	else {
		cout << "û���ҵ�IDΪ��" << bookid << "���鼮" << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//չʾͼ���б�
bool Manage::ShowBookList()
{
	vector<Book> books;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	int sum=0;
	new_mysql.SelectAllBook(books,sum);
	cout << "����ѯ�� " << sum << " �������" << endl;
	vector<Book>::iterator vecIter;
	cout << "ID     ����            ����           ������       �������     �ݲ�����   ����" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
	}
	return true;
}

//չʾ���ļ�¼
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
	cout << "����ѯ�� " << sum << " �������" << endl;
	cout << "ID     ����            ������           ��������       Ӧ������        ʵ������		�������" << endl;
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

//�����û�
bool Manage::AddNewUser()
{
	string name, passwd;
	//int role;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	cout << "�������û���Ϣ��" << endl;
	cout << "�û���		����			����" << endl;
	User user;
	cin >> user.strName;
	cin >> user.strPassword;
	cin >> user.Role;
	new_mysql.AddUser(user);
	cout << "�����û��ɹ�" << endl;
	cin.get();
	cin.get();
	return true;
}

//չʾ�û��б�
bool Manage::ShowUserList()
{
	vector<User>users;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	int sum=-1;
	new_mysql.QueryAllUser(users,sum);
	cout << "����ѯ����" << sum << " �����" << endl;
	vector<User>::iterator vecIter;
	cout << "ID     �û���      ���" << endl;
	for (vecIter = users.begin(); vecIter != users.end(); vecIter++)
	{
		cout << setiosflags(ios::left) << setw(6) << vecIter->Id << "  " << setw(8) << vecIter->strName << "  " << (vecIter->Role == 1 ? "����Ա" : "ѧ��") << endl;
	}
	cin.get();
	cin.get();
	return true;
}