#pragma once

#include<string>
using namespace std;
class User
{
public:
	User();				//User类的构造函数声明
	//User(int id, string name, string pass, int role) :Id(id), strName(name), strPassword(pass), Role(role) {};
	~User();			//User类的折构函数声明

public:
	int Id;					//用户Id
	string strName;			//用户账号
	string strPassword;		//用户密码
	int Role;				//用户身份	1-管理员		2-普通用户
};

