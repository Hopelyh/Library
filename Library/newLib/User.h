#pragma once

#include<string>
using namespace std;
class User
{
public:
	User();				//User��Ĺ��캯������
	//User(int id, string name, string pass, int role) :Id(id), strName(name), strPassword(pass), Role(role) {};
	~User();			//User����۹���������

public:
	int Id;					//�û�Id
	string strName;			//�û��˺�
	string strPassword;		//�û�����
	int Role;				//�û����	1-����Ա		2-��ͨ�û�
};

