//
// Created by jjt on 2022/4/10.
//

#ifndef BIF2XMLBIF_HELPER_H
#define BIF2XMLBIF_HELPER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string double2string(double do_b);
string TrimRight(string s);
string TrimRightComma(string s);
string TrimRightSemicolon(string s);
string TrimLeft(string s);
string Trim(string &s);
vector<string> Split(string &s, string delimiter);

#endif //BIF2XMLBIF_HELPER_H
