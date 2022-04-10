//
// Created by jjt on 2022/4/8.
//
#include "helper.h"

string double2string(double do_b) {
    string str1;
    stringstream ss;
    ss<<do_b;
    ss>>str1;
    return str1;
}

/**
 * @brief: trim all \t, \n, \r and whitespace characters on the right of a string.
 */
string TrimRight(string s) {
    while (!s.empty() && s[s.size()-1]<33) { // ASCII. \t=09, \n=10, \r=13, space=32.
        s.erase(s.size()-1);
    }
    return s;
}

string TrimRightComma(string s) {
    if (s[s.size()-1] == 44) { // ASCII: ,=44
        s.erase(s.size()-1);
    }
    return s;
}

string TrimRightSemicolon(string s) {
    if (s[s.size()-1] == 59) { // ASCII: ;=59
        s.erase(s.size()-1);
    }
    return s;
}

/**
 * @brief: trim all \t, \n, \r and whitespace characters on the left of a string.
 */
string TrimLeft(string s) {
    while (!s.empty() && s[0]<33) { // ASCII. \t=09, \n=10, \r=13, space=32.
        s.erase(0, 1);
    }
    return s;
}

/**
 * @brief: trim all \t, \n, \r and whitespace characters on the left or right of a string.
 */
string Trim(string &s) {
    return TrimLeft( TrimRight(s) );
}

/**
 * @brief: split string s into a vector of strings by the delimiter
 */
vector<string> Split(string &s, string delimiter) {
    vector<string> result;
    size_t begin = 0, end = 0;
    while ((end=s.find_first_of(delimiter, begin)) != string::npos) {
        result.push_back(s.substr(begin, end-begin));
        begin = (++end);
    }
    result.push_back(s.substr(begin, s.size()-begin)); // the last one
    return result;
}
