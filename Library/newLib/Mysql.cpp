#include"Mysql.h"
#include"Book.h"



Mysql::Mysql()					//���ݿ�������Ĺ��캯��
{
	Username = "root";			//�û���
	Pswd = "hl20010405";			//����
	Host = "localhost";			//������
	Database = "library";		//���ݿ�����
	Port = 3306;				//�˿ں�
	isOpen = false;

}

Mysql::~Mysql()					//���ݿ���������۹�����
{
	CloseMysql();
}

//�����ݿ�
bool Mysql::OpenMysql()
{
	mysql_init(&mysql);			//��ʼ��mysql;

	//c_str()������ͷ�ļ�<cstring>�У����ڽ�stringת��ΪC����ַ���
	//true��ʾ���ӳɹ��������������������û��������룬���ݿ����֣��˿ں�
	if (mysql_real_connect(&mysql, Host.c_str(), Username.c_str(), Pswd.c_str(), Database.c_str(), Port, NULL, 0) ){
		isOpen = true;
		return true;
	}
	else {
		return false;
	}
}

//�ر����ݿ�
bool Mysql::CloseMysql()
{
	mysql_free_result(result);
	mysql_close(&mysql);
	return true;
}

/*--------------------���ݿ����------------------
���е����ݿ����������д��SQL��䣬Ȼ����mysql_query(&mysql,query)����ɣ������������ݿ�����ɾ�Ĳ�
��ѯ����
*/

//�����û�
bool Mysql::AddUser(User user)
{
	string sql = "";
	char RoleType[16];
	sprintf_s(RoleType, "%d", user.Role);			//���͸�ʽ�������RoleType��ָ����ַ���

	if(isOpen)
	{
		sql += "insert into user values(null,'" + user.strName + "','" + user.strPassword + "'," + RoleType + ")";
		mysql_query(&mysql, sql.c_str());

	}
	else {
		cout << "connect failed!" << endl;
	}
	return true;
}

//����ͼ��
bool Mysql::AddBook(Book book)
{
	string sql;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		sql+="insert into book values(null,'"+book.GetBookName()+"','"+book.GetBookAuthor()+"','"+book.GetBookISBN()+"','"+
			book.GetBookPub() + "','" + book.GetBookInDate() + "'," + to_string(book.GetBookTotal())+ "," + to_string(book.GetBookLeft())+")";
		mysql_query(&mysql, sql.c_str());
	}
	else {
		cout << "connect failed" << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//�����û������������û���Ϣ
User Mysql::ReadUser(string strUsername, string strUserPswd)
{
	User user;
	char column[32][32];
	int res;
	string sql;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");		//���ñ����ʽ��������cmd���޷���ʾ����
		//SQL���Ϊ���������˺ź������ѯ�û���Ϣ
		sql += "select * from user where name= '" + strUsername + "' and password='" + strUserPswd + "'";
		res=mysql_query(&mysql, sql.c_str());			//��ѯ
		if (!res)
		{
			result = mysql_store_result(&mysql);			//�����ѯ�������ݵ�result
			if (result->row_count > 0)
			{
				int i, j;
				//cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
				for (i = 0; fd = mysql_fetch_field(result); i++)		//mysql_fetch_field������һ���ֶε�����
				{
					strcpy_s(column[i], fd->name);
				}
				j = mysql_num_fields(result);		//���ؽ�������е�����

				if (j > 0)
				{
					sql_row = mysql_fetch_row(result);			//�ӽ������ȡ����һ��
					user.Id = atoi(sql_row[0]);
					user.strName = sql_row[1];
					user.Role = atoi(sql_row[3]);
				}
			}
			else {					//resultС��0
				user.Id = -1;
				return user;
			}
		}
		else
		{
			cout << "query sql failed!" << endl;
		}
	}
	else {
		cout << "connect failed" << endl;

	}
	if (result != NULL)
	{
		mysql_free_result(result);				//�ͷŽ����Դ
	}

	return user;
}

//��������ͼ��
bool Mysql::SelectAllBook(vector<Book>& books,int sum)
{
	string sql;
	if (isOpen)
	{
		sql += "select * from book";
		mysql_query(&mysql, "SET NAMES GBK");
		if (mysql_query(&mysql, sql.c_str()))
		{
			cout << "query sql failed" << endl;
		}
		else {
			result = mysql_store_result(&mysql);
			if (result)
			{
				sum = mysql_affected_rows(&mysql);
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					Book book;
					book.SetBookId(atoi(sql_row[0]));
					book.SetBookName(sql_row[1]);
					book.SetBookAuthor(sql_row[2]);
					book.SetBookISBN(sql_row[3]);
					book.SetBookPub(sql_row[4]);
					book.SetBookInDate(sql_row[5]);
					book.SetBookTotal(atoi(sql_row[6]));
					book.SetBookLeft(atoi(sql_row[7]));
					books.push_back(book);
				}
			}
		}
	}
	else {
		cout << "connect failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}

//����������ѯ�鼮
bool Mysql::QueryBookName(string strBookName,vector<Book> &books,int sum)
{
	Book book;
	string sql;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");
		sql += "select * from book where bookname like'%" + strBookName + "%'";
		if (!mysql_query(&mysql, sql.c_str()))
		{
			result = mysql_store_result(&mysql);
			if (result)
			{
				sum = mysql_affected_rows(&mysql);
				while (sql_row = mysql_fetch_row(result))
				{
					Book book;
					book.SetBookId(atoi(sql_row[0]));
					book.SetBookName(sql_row[1]);
					book.SetBookAuthor(sql_row[2]);
					book.SetBookISBN(sql_row[3]);
					book.SetBookPub(sql_row[4]);
					book.SetBookInDate(sql_row[5]);
					book.SetBookTotal(atoi(sql_row[6]));
					book.SetBookLeft(atoi(sql_row[7]));
					books.push_back(book);
				}
			}
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}

//����ͼ��ID��ѯ�鼮
bool Mysql::QueryBookId(int bookid,Book& book)
{
	string sql;
	char id[5];
	sprintf_s(id, "%d", bookid);
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");
		sql += "select * from book where id = ";
		sql += id;
		if (!mysql_query(&mysql, sql.c_str()))
		{
			result = mysql_store_result(&mysql);
			if (result)
			{
				sql_row = mysql_fetch_row(result);
				book.SetBookId(atoi(sql_row[0]));
				book.SetBookName(sql_row[1]);
				book.SetBookAuthor(sql_row[2]);
				book.SetBookISBN(sql_row[3]);
				book.SetBookPub(sql_row[4]);
				book.SetBookInDate(sql_row[5]);
				book.SetBookTotal(atoi(sql_row[6]));
				book.SetBookLeft(atoi(sql_row[7]));
			}
			else {
				book.SetBookId(-1);
			}
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}

//����ͼ��IDɾ���鼮
bool Mysql::DeleteBookId(int bookid)
{
	string sql;
	//char temp[5] = { 0 };
	//sprintf(temp, "%d", bookid);
	if (isOpen)
	{
		sql+= "delete from book where id ="+to_string(bookid);
		//sql += temp;
		if (!mysql_query(&mysql, sql.c_str()))
		{
			cout << "Delete Success!" << endl;
		}
		else 
		{
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	return true;
}

//�������ļ�¼
bool Mysql::AddBorrowRecord(BorrowRecord record)
{
	string sql="";
	if (isOpen)
	{
		sql += "insert into borrowrecord values(NULL,'" + to_string(record.r_bookid) + "','" + to_string(record.r_userid) + "','" + record.borrowdate;
		sql += "','" + record.shouldreturndate + "','" + record.returndate + "',0)" ;
		mysql_query(&mysql, sql.c_str());

		//ͼ��������1
		sql = "";
		sql += "update book set book.left = book.left-1 where bookid =" + to_string(record.r_bookid);
		mysql_query(&mysql, sql.c_str());
		cout << "���ĳɹ���" << endl;
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	return true;
}

//�����û�ID��ѯ�û���Ϣ
User Mysql::QueryUserId(int userid)
{
	string sql = "";
	User user;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");
		sql += "select * from user where id =" + userid;
		if (!mysql_query(&mysql, sql.c_str())) {
			result = mysql_store_result(&mysql);
			sql_row = mysql_fetch_row(result);			//�ӽ������ȡ����һ��
			user.Id = atoi(sql_row[0]);
			user.strName = sql_row[1];
			user.Role = atoi(sql_row[3]);
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return user;
}

//��ѯ���н��ļ�¼
bool Mysql::QueryAllRecord(vector<BorrowRecord>& borrowrecords,int sum)
{
	string sql="";
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");
		sql += "select *from borrowrecor";
		if (!mysql_query(&mysql, sql.c_str()))
		{
			result = mysql_store_result(&mysql);
			if (result)
			{
				sum = mysql_affected_rows(&mysql);
				while (sql_row = mysql_fetch_row(result))
				{
					BorrowRecord record;
					record.r_id = atoi(sql_row[0]);
					record.r_bookid = atoi(sql_row[1]);
					record.r_userid = atoi(sql_row[2]);
					record.borrowdate = sql_row[3];
					record.shouldreturndate = sql_row[4];
					record.returndate = (sql_row[5] == NULL ? "" : sql_row[5]);
					record.re_bo_times = atoi(sql_row[6]);
					borrowrecords.push_back(record);
				}
			}
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}

//��ѯĳλ�û��Ľ��ļ�¼
bool Mysql::QueryUserRecord(vector<BorrowRecord> records, int userid,int sum)
{
	
	string sql;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");
		sql += "select * from borrowrecord where userid =" + to_string(userid);
		if (!mysql_query(&mysql, sql.c_str()))
		{
			result = mysql_store_result(&mysql);
			sum = mysql_affected_rows(&mysql);
			while (sql_row = mysql_fetch_row(result))
			{
				BorrowRecord record;
				record.r_id = atoi(sql_row[0]);
				record.r_bookid = atoi(sql_row[1]);
				record.r_userid = atoi(sql_row[2]);
				record.borrowdate = sql_row[3];
				record.shouldreturndate = sql_row[4];
				record.returndate = (sql_row[5] == NULL ? "" : sql_row[5]);
				record.re_bo_times = atoi(sql_row[6]);
				records.push_back(record);
			}
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}

//�黹�鼮
bool Mysql::ReturnBook(int recordid, int bookid)
{
	string sql="";
	time_t return_time = time(NULL);
	char ch[16];
	
	newtime.TimeToString(return_time, ch);
	string s=ch;
	if (isOpen)
	{
		sql += "update borrowrecord set returndate =" + s + "where id =" + to_string(recordid);
		if (!mysql_query(&mysql, sql.c_str()))
		{
			sql = "";
			sql += "update book set book.left=book.left+1 where id =" + bookid;
			mysql_query(&mysql, sql.c_str());
		}
		else {
			cout<<"Query Failed!"<<endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	return true;
}

//��ѯ�����û���Ϣ
bool Mysql::QueryAllUser(vector<User> users, int sum)
{
	string sql="";
	int res;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");
		sql += "select * from user";
		res = mysql_query(&mysql, sql.c_str());
		if (!res)
		{
			result = mysql_store_result(&mysql);
			sum = mysql_affected_rows(&mysql);
			while (sql_row = mysql_fetch_row(result)) 
			{
				User user;
				user.Id = atoi(sql_row[0]);
				user.strName = sql_row[1];
				user.Role = atoi(sql_row[3]);
				users.push_back(user);
			}
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}

//����ͼ��
bool Mysql::RenewBook(int recordid)
{
	string sql, renew;
	time_t renewtime = time(NULL);
	renew = newtime.AddMonth(renewtime);
	if (isOpen)
	{
		sql += "update borrowrecord set shouldreturn = " + renew + "where id =" + to_string(recordid);
		if (!mysql_query(&mysql, sql.c_str()))
		{
			cout << "����ɹ�" << endl;
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	return true;
}

//���ݼ�¼id��ѯ��¼
bool Mysql::QueryRecordId(BorrowRecord record, int recordid)
{
	string sql="";
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");
		sql += "select * from borrowrecord where id =" + to_string(recordid);
		if (!mysql_query(&mysql, sql.c_str()))
		{
			result = mysql_store_result(&mysql);
			sql_row = mysql_fetch_row(result);
			record.r_id = atoi(sql_row[0]);
			record.r_bookid = atoi(sql_row[1]);
			record.r_userid = atoi(sql_row[2]);
			record.borrowdate = sql_row[3];
			record.shouldreturndate = sql_row[4];
			record.returndate = (sql_row[5] == NULL ? "" : sql_row[5]);
			record.re_bo_times = atoi(sql_row[6]);
		}
		else {
			cout << "Query Failed!" << endl;
		}
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	if (result != NULL)
	{
		mysql_free_result(result);
	}
	return true;
}


