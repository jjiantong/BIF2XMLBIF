//
// Created by jjt on 27/7/2022.
//

#ifndef BIF2XMLBIF_VARIABLE_H
#define BIF2XMLBIF_VARIABLE_H

#include "helper.h"

class Variable {
public:
    int id;
    string name;
    int num_poss_vals;
    vector<string> poss_vals;
    int num_par;
    vector<string> pars;
    int table_size;
    vector<double> table;
    string s_table;

    Variable(int id);
};



#endif //BIF2XMLBIF_VARIABLE_H
