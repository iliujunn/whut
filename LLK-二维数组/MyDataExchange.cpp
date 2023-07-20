#include "pch.h"
#include "MyDataExchange.h"

MyDataExchange::MyDataExchange() {
	driver = sql::mysql::get_driver_instance();
	con = driver->connect("tcp://....", "root", "12138");
	con->setSchema("LLK");
}
MyDataExchange::~MyDataExchange() {
	if (con) delete con;
	if (driver) delete driver;
}

void MyDataExchange::getData(std::vector<int>& data) {
	try {
		sql::Statement* querySql = con->createStatement();
		sql::ResultSet* res = querySql->executeQuery("select * from gamerank order by timecost asc");
		while (res->next()) {
			data.push_back(res->getInt("timecost"));
		}
		delete res;
		delete querySql;
	}
	catch (sql::SQLException& e) {
		throw e;
	}
}

void MyDataExchange::insertIntoDB(int time) {
	try {
		sql::PreparedStatement* insertSql = con->prepareStatement("insert into gamerank (timecost) values (?)");
		insertSql->setInt(1, time);
		insertSql->execute();

		delete insertSql;
	}
	catch (sql::SQLException& e) {
		throw e;
	}
}