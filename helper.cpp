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

void CorrectTemplate(ifstream &in_file) {
    string line;
    /**
     * 1. "network"
     * network unknown {
     * }
     */
    getline(in_file, line);
    vector<string> parsed_line = Split(line, " ");
    cout << "network name = " << parsed_line.at(1) << endl;
    getline(in_file, line);

    /**
     * 2. "variable"
     * variable BirthAsphyxia {
     *  type discrete [ 2 ] { yes, no };
     * }
     * variable HypDistrib {
     *  type discrete [ 2 ] { Equal, Unequal };
     * }
     */
    getline(in_file, line);
    // if there is a whitespace at the beginning  of the line
    // it will cause a bug if we do not trim it
    line = TrimLeft(line);
    parsed_line = Split(line, " ");

    while (parsed_line.at(0).compare("probability") != 0) { // it is about variable
        while (parsed_line.at(0).compare("}") != 0) {
            if (parsed_line.at(0).compare("variable") == 0) { // case 1: variable BirthAsphyxia {
                cout << "node name = " << parsed_line.at(1) << endl;
            } else if (parsed_line.at(0).compare("type") == 0) {
                cout << "type = " << parsed_line.at(1) << endl;

                int num_vals = atoi(parsed_line.at(3).c_str());
                for (int i = 6; i < 6 + num_vals; ++i) {
                    cout << "  - possible value - " << TrimRightComma(parsed_line.at(i)) << endl;
                }
            }
            getline(in_file, line);
            line = TrimLeft(line);
            parsed_line = Split(line, " ");
        }

        getline(in_file, line);
        line = TrimLeft(line);
        parsed_line = Split(line, " ");
    }

    /**
     * 3. "probability"
     * probability ( LowerBodyO2 | HypDistrib, HypoxiaInO2 ) {
     *  (Equal, Mild) 0.1, 0.3, 0.6;
     *  (Unequal, Mild) 0.4, 0.5, 0.1;
     *  (Equal, Moderate) 0.3, 0.6, 0.1;
     *  (Unequal, Moderate) 0.50, 0.45, 0.05;
     *  (Equal, Severe) 0.5, 0.4, 0.1;
     *  (Unequal, Severe) 0.60, 0.35, 0.05;
     * }
     */
    while (!in_file.eof()) {
        // these two lines have to be at the beginning of the while loop, not the end
        line = TrimLeft(line);
        parsed_line = Split(line, " ");

        int num_par = -1;
        vector<double> table;

        while (parsed_line.at(0).compare("}") != 0) {
            if (parsed_line.at(0).compare("probability") == 0) {
                if (parsed_line.at(3).compare(")") != 0) { // has parents
                    cout << "for node " << parsed_line.at(2) << endl;

                    int pos = 4;
                    while (parsed_line.at(pos).compare(")") != 0) {
                        cout << " - par - " << TrimRightComma(parsed_line.at(pos)) << endl;
                        ++pos;
                    }
                    num_par = pos - 4;
                } else { // no parents
                    num_par = 0;
                    cout << "for node " << parsed_line.at(2) << endl;
                    cout << " - no par - " << endl;
                }
            } else {
                if (num_par > 0) { // has parents
                    for (int i = num_par; i < parsed_line.size(); ++i) {
                        string p1 = TrimRightSemicolon(parsed_line.at(i));
                        string p2 = TrimRightComma(p1);
                        double potential = atof(p2.c_str());
                        table.push_back(potential);
                    }
                } else { // no parents
                    for (int i = 1; i < parsed_line.size(); ++i) {
                        string p1 = TrimRightSemicolon(parsed_line.at(i));
                        string p2 = TrimRightComma(p1);
                        double potential = atof(p2.c_str());
                        table.push_back(potential);
                    }
                }
            }
            getline(in_file, line);
            line = TrimLeft(line);
            parsed_line = Split(line, " ");
        }

        string s;
        for (int i = 0; i < table.size(); ++i) {
            s += double2string(table[i]);
            s += " ";
        }
        cout << "table = " << s << endl;

        getline(in_file, line);
    }

}