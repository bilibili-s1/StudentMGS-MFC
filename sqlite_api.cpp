#include <iostream>
#include "sqlite3.h"
#include <string>
#include "student.h"
#include "class.h"
#include "grade.h"
#include "school.h"
#include "sqlite_api.h"
#include <vector>
#include <iomanip>
using namespace std;
int CSqlite_api::sql_delete(sqlite3* db,int grade,int iClass, int id) {
    const char* sql = "DELETE FROM Students WHERE (id = ? and grade = ? and class = ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return rc;/*fprintf(stderr, "准备删除失败: %s\n", sqlite3_errmsg(db));*/
    }

    sqlite3_bind_int(stmt, 1, id); // 设置要删除的ID
    sqlite3_bind_int(stmt, 2, grade); // 设置要删除的ID
    sqlite3_bind_int(stmt, 3, iClass); // 设置要删除的ID
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        return rc;/*fprintf(stderr, "执行删除失败: %s\n", sqlite3_errmsg(db));*/
    }

    sqlite3_finalize(stmt);
}
int CSqlite_api::initialize(sqlite3* db, vector<CStudent> &studentvector) {
    int rc = SQLITE_ERROR;
    char* errmsg;
    char sql[1024] = { 0 };

    int ncolumn;

    sqlite3_stmt* stmt;
    strcpy_s(sql, "select * from students");

    rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);
    if (rc)
    {
        return rc;
    }
    else
    {
        int i = 0;
        rc = sqlite3_step(stmt);//查询成功，则返回值rc==SQLITE_ROW
        ncolumn = sqlite3_column_count(stmt);//获取列数
        CStudent student;
        while (rc == SQLITE_ROW)
        {
            student.set_grade(sqlite3_column_int(stmt, 0));
            student.set_cla(sqlite3_column_int(stmt, 1));
            student.set_id(sqlite3_column_int(stmt, 2));
            std::string str = (char*)sqlite3_column_text(stmt, 3);
            student.set_name(str);
            student.set_ch(sqlite3_column_int(stmt, 4));
            student.set_ms(sqlite3_column_int(stmt, 5));
            student.set_en(sqlite3_column_int(stmt, 6));
            //push back to studentvector
            studentvector.push_back(student);
            rc = sqlite3_step(stmt);//继续获取下一行数据
            i++;
        }
    }
    sqlite3_finalize(stmt);
    return rc;
}
int CSqlite_api::print_table(void* data, int columns, char** values, char** fileds) {
    cout << "\ndata(now):" << *(int*)data<<endl;
    for (size_t i = 0; i < columns; i++) {
        cout << setw(7)<<fileds[i] << "|";
    }
    cout << "\n";
    for (size_t i = 0; i < columns; i++) {
        cout <<setw(7)<< values[i] << "|";
    }
    return SQLITE_OK;


}
int CSqlite_api::insert_sql(sqlite3* db,int grade,int classes,string name,int id,int ch,int ms,int en) {
    int rc = SQLITE_ERROR;
    char sqll[1024] = { 0 };
    sprintf_s(sqll, "INSERT INTO students(grade,class,id,name,chinese,maths,english) VALUES(%d,%d,%d,'%s',%d,%d,%d)",grade, classes, id, name.c_str(),ch, ms,en);
    rc = sqlite3_exec(db, sqll, NULL, NULL, NULL);
    return rc;

}
int  CSqlite_api::creat_table(sqlite3* db) {
    int rc = SQLITE_ERROR;
    rc = sqlite3_exec(db, "CREATE TABLE students(grade INT,class INT,id INT,name VARCHAR(50),chinese INT,maths INT,english INT)", NULL, NULL, NULL);
    return rc;
}

