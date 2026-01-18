#include <iostream>
#include <string>
#include <sqlite3.h>
#include "class.h"
#include "grade.h"
#include "school.h"
#include "student.h"

string CStudent::get_name() {
    return name;
}
void CStudent::set_name(string a) {
    name = a;

}
int CStudent::get_id() {
    return id;
}
void CStudent::set_id(int a) {
    id = a;
}
void CStudent::set_ch(int a) {
    chinese = a;
}
void CStudent::set_ms(int a) {
    maths = a;
}
void CStudent::set_en(int a) {
    english = a;
}
int CStudent::get_ch() {
    return chinese;
}
int CStudent::get_ms() {
    return maths;
}
int CStudent::get_en() {
    return english;
}
void CStudent::set_grade(int a) {
    gra->set_gra(a);
}
void CStudent::set_cla(int a) {
    classs->set_clah(a);
}
int CStudent::get_cla() {
    return classs->get_clah();
}
int CStudent::get_gra() {
    return gra->get_gra();
}
