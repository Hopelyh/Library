#include"Student.h"
Student::~Student()
{

}

//�˵�չʾ
bool Student::ShowMenu()
{
	system("cls");
	cout << "==========================��ӭʹ��ͼ��ݺ�̨����ϵͳ��==========================" << endl;
	cout << "                              1.��ѯͼ��" << endl;
	cout << "                              2.����ͼ��" << endl;
	cout << "                              3.�黹ͼ��" << endl;
	cout << "                              4.���ļ�¼" << endl;
	cout << "                              5.����ͼ��" << endl;
	cout << "                              0.�˳���¼" << endl;
	return true;
}

//����������ѯ
bool Student::QueryBook()
{
	string name;
	cout << "����������:" << endl;
	cin >> name;
	if (!new_mysql.isOpen)
	{
		new_mysql.OpenMysql();
	}
	vector<Book>books;
	int sum=-1;
	new_mysql.QueryBookName(name, books, sum);				//���ز�ѯ
	vector<Book>::iterator vecIter;
	cout << "����ѯ����" << sum << " �����";
	cout << "ID     ����            ����           ������       �������     �ݲ�����   ����" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookId() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetBookAuthor() << "  " << setw(14) << vecIter->GetBookPub() << "  " << setw(14) << vecIter->GetBookInDate() << "  " << setw(8) << vecIter->GetBookTotal() << "  " << setw(3) << vecIter->GetBookLeft() << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//����ͼ��
bool Student::BorrowBook(int userid)
{
	QueryBook();
	int id;
	cout << "����������Ҫ���ĵ��鼮ID:" << endl;
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
		cout << "�����Ƿ�Ҫ���ı��飺(y/n)" << endl;
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
				new_time.TimeToString(time1, ch);					//����ʱ��תtime
				new_record.shouldreturndate = new_time.AddMonth(time1);
				new_record.returndate = "";
				new_record.re_bo_times = 0;
				book.SetBookLeft(book.GetBookLeft() - 1);
				new_mysql.AddBorrowRecord(new_record);
				//cout << "���ĳɹ�" << endl;
				break;
			}
			else if (ch == 'n' || ch == 'N')
			{
				cout << "��ȡ����" << endl;
				break;
			}
			else {
				cout << "�����������������" << endl;
				cin.get();
				continue;
			}
		}

	}
	else {
		cout << "���鼮�Ѿ�ȫ��������޷����ģ�" << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//�黹ͼ��
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
	cout << "��ѯ�����Ľ�����Ϣ����,�� "<<sum<<" ��" << endl;
	cout << "ID		����			������			����ʱ��			Ӧ��ʱ��			�������" << endl;
	vector<BorrowRecord>::iterator vecIter = records.begin();
	for (; vecIter != records.end(); vecIter++)
	{
		new_mysql.QueryBookId(vecIter->r_bookid, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->r_id << "   " << setw(14) << book.GetBookName() << "   " << setw(14) << book.GetBookPub()
			<< "   " << setw(14) << vecIter->borrowdate << "   " << setw(14) << vecIter->shouldreturndate << "   " << setw(10) << vecIter->re_bo_times;
				
	}
	int re_id;
	cout << "��������Ҫ�黹��ͼ����ļ�¼ID��" << endl;
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
			cout << "�������ID���ڼ�¼�У����������룺" << endl;
		}
	}
	new_mysql.ReturnBook(re_id, vecIter->r_bookid);
	cout << "����ɹ���" << endl;
	cin.get();
	cin.get();
	return true;	
}

//���ļ�¼
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
	cout << "��ѯ�����Ľ�����Ϣ " << sum << " ����" << endl; 
	cout << "ID		����			������			����ʱ��			Ӧ��ʱ��			�������" << endl;
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

//����ͼ��
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
	cout << "��ѯ�����Ľ�����Ϣ " << sum << " ����" << endl;
	cout << "ID		����			������			����ʱ��			Ӧ��ʱ��			�������" << endl;
	vector<BorrowRecord>::iterator vecIter = records.begin();
	for (; vecIter != records.end(); vecIter++)
	{
		new_mysql.QueryBookId(vecIter->r_bookid, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->r_id << "   " << setw(14) << book.GetBookName() << "   " << setw(14) << book.GetBookPub()
			<< "   " << setw(14) << vecIter->borrowdate << "   " << setw(14) << vecIter->shouldreturndate << "   " << setw(10) << vecIter->re_bo_times;
	}
	cout << "��������Ҫ�����ͼ����ļ�¼ID��" << endl;
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
			cout << "�������ID���ڼ�¼�У����������룺" << endl;
		}
	}
	new_mysql.RenewBook(re_id);
	cout << "����ɹ�!" << endl;
	cin.get();
	cin.get();
	return true;
}