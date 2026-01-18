#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>
#include "class.h"
#include "grade.h"
#include "school.h"
using namespace std;
class CStudent {
public:
    string get_name();
    void set_name(string a);
    int get_id();
    void set_id(int a);
    void set_ch(int a);
    int get_ch();
    void set_ms(int a);
    int get_ms();
    void set_en(int a);
    int get_en();
    void set_grade(int a);
    void set_cla(int a);
    int get_cla();
    int get_gra();
private:
    CSchool sch[4];
    CGrade gra[6];
    CClass classs[30];
    string name;
    int id = 1;
    int chinese = 0;
    int maths = 0;
    int english = 0;
};