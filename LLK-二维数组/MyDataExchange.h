#pragma once
#include "mysql/jdbc.h"
#include"vector"
class MyDataExchange
{
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;

public:
	void getData(std::vector<int>& data);
	void insertIntoDB(int);
	MyDataExchange();
	~MyDataExchange();
};


