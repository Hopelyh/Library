#include"Mysql.h"
#include"Book.h"



Mysql::Mysql()					//数据库连接类的构造函数
{
	Username = "root";			//用户名
	Pswd = "hl20010405";			//密码
	Host = "localhost";			//主机名
	Database = "library";		//数据库名字
	Port = 3306;				//端口号
	isOpen = false;

}

Mysql::~Mysql()					//数据库连接类的折构函数
{
	CloseMysql();
}

//打开数据库
bool Mysql::OpenMysql()
{
	mysql_init(&mysql);			//初始化mysql;

	//c_str()包含在头文件<cstring>中，用于将string转换为C风格字符串
	//true表示连接成功，参数依次主机名，用户名，密码，数据库名字，端口号
	if (mysql_real_connect(&mysql, Host.c_str(), Username.c_str(), Pswd.c_str(), Database.c_str(), Port, NULL, 0) ){
		isOpen = true;
		return true;
	}
	else {
		return false;
	}
}

//关闭数据库
bool Mysql::CloseMysql()
{
	mysql_free_result(result);
	mysql_close(&mysql);
	return true;
}

/*--------------------数据库操作------------------
所有的数据库操作都是先写个SQL语句，然后用mysql_query(&mysql,query)来完成，包括创建数据库或表，增删改查
查询数据
*/

//增加用户
bool Mysql::AddUser(User user)
{
	string sql = "";
	char RoleType[16];
	sprintf_s(RoleType, "%d", user.Role);			//发送格式化输出到RoleType所指向的字符串

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

//新增图书
bool Mysql::AddBook(Book book)
{
	string sql;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
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

//根据用户名和密码获得用户信息
User Mysql::ReadUser(string strUsername, string strUserPswd)
{
	User user;
	char column[32][32];
	int res;
	string sql;
	if (isOpen)
	{
		mysql_query(&mysql, "SET NAMES GBK");		//设置编码格式，否则在cmd下无法显示中文
		//SQL语句为根据输入账号和密码查询用户信息
		sql += "select * from user where name= '" + strUsername + "' and password='" + strUserPswd + "'";
		res=mysql_query(&mysql, sql.c_str());			//查询
		if (!res)
		{
			result = mysql_store_result(&mysql);			//保存查询到的数据到result
			if (result->row_count > 0)
			{
				int i, j;
				//cout << "number of result: " << (unsigned long)mysql_num_rows(result) << endl;
				for (i = 0; fd = mysql_fetch_field(result); i++)		//mysql_fetch_field返回下一个字段的类型
				{
					strcpy_s(column[i], fd->name);
				}
				j = mysql_num_fields(result);		//返回结果集中列的数量

				if (j > 0)
				{
					sql_row = mysql_fetch_row(result);			//从结果集中取得下一行
					user.Id = atoi(sql_row[0]);
					user.strName = sql_row[1];
					user.Role = atoi(sql_row[3]);
				}
			}
			else {					//result小于0
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
		mysql_free_result(result);				//释放结果资源
	}

	return user;
}

//搜索所有图书
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
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
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

//根据书名查询书籍
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

//根据图书ID查询书籍
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

//根据图书ID删除书籍
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

//新增借阅记录
bool Mysql::AddBorrowRecord(BorrowRecord record)
{
	string sql="";
	if (isOpen)
	{
		sql += "insert into borrowrecord values(NULL,'" + to_string(record.r_bookid) + "','" + to_string(record.r_userid) + "','" + record.borrowdate;
		sql += "','" + record.shouldreturndate + "','" + record.returndate + "',0)" ;
		mysql_query(&mysql, sql.c_str());

		//图书余量减1
		sql = "";
		sql += "update book set book.left = book.left-1 where bookid =" + to_string(record.r_bookid);
		mysql_query(&mysql, sql.c_str());
		cout << "借阅成功！" << endl;
	}
	else {
		cout << "Connect Failed!" << endl;
	}
	return true;
}

//根据用户ID查询用户信息
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
			sql_row = mysql_fetch_row(result);			//从结果集中取得下一行
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

//查询所有借阅记录
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

//查询某位用户的借阅记录
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

//归还书籍
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

//查询所有用户信息
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

//续借图书
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
			cout << "续借成功" << endl;
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

//根据记录id查询记录
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


