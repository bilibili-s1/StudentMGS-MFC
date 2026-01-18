#pragma once
#include <sqlite3.h>
using namespace std;
#include "student.h"
#include <vector>
class CSqlite_api {
public:
	//删除函数：
	int sql_delete(sqlite3* db, int grade,int iClass,int id);
	//初始化：
	int initialize(sqlite3* db, vector<CStudent> &stuarr);
	//打印：
	static int print_table(void* data, int columns, char** values, char** fileds);
     int insert_sql(sqlite3* db, int grade, int classes, string name, int id, int ch, int ms, int en);
	int creat_table(sqlite3* db);
};