//
// Created by jjt on 27/7/2022.
//

#include "network.h"

Network::Network() {
    num_of_vars = 0;
}

void Network::LoadNetworkFile(ifstream &in_file) {
    string line;
    /**
     * 1. "network"
     * network unknown {
     * }
     */
    getline(in_file, line);
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
    vector<string> parsed_line = Split(line, " ");

    int id = 0;
    while (parsed_line.at(0).compare("probability") != 0) { // it is about variable
        Variable *var = new Variable(id++);

        while (parsed_line.at(0).compare("}") != 0) {
            if (parsed_line.at(0).compare("variable") == 0) { // case 1: variable BirthAsphyxia {
                var->name = parsed_line.at(1);
            } else if (parsed_line.at(0).compare("type") == 0) {
                var->num_poss_vals = atoi(parsed_line.at(3).c_str());
                for (int i = 6; i < 6 + var->num_poss_vals; ++i) {
                    var->poss_vals.push_back(TrimRightComma(parsed_line.at(i)));
                }
            }
            getline(in_file, line);
            line = TrimLeft(line);
            parsed_line = Split(line, " ");
        }

        this->all_vars.push_back(var);
        this->num_of_vars++;

        getline(in_file, line);
        line = TrimLeft(line);
        parsed_line = Split(line, " ");
    }

//    cout << "num of nodes in the network = " << this->num_of_vars << endl;

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
    id = 0;
    while (!in_file.eof()) {
        Variable *var = this->all_vars[id++];
        // these two lines have to be at the beginning of the while loop, not the end
        line = TrimLeft(line);
        parsed_line = Split(line, " ");

        int num_par = -1;
        vector<double> table;

        while (parsed_line.at(0).compare("}") != 0) {
            if (parsed_line.at(0).compare("probability") == 0) {
                if (parsed_line.at(3).compare(")") != 0) { // has parents

                    int pos = 4;
                    while (parsed_line.at(pos).compare(")") != 0) {
                        string par = TrimRightComma(parsed_line.at(pos));
                        var->pars.push_back(par);
                        ++pos;
                    }
                    num_par = pos - 4;
                    if (num_par != var->pars.size()) {cout << "!!!!" << endl; }
                } else { // no parents
                    num_par = 0;
                }
                var->num_par = num_par;
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

        var->table = table;
        var->table_size = table.size();

        getline(in_file, line);
    }

//    cout << "finish loading network" << endl;


    for (int i = 0; i < this->num_of_vars; ++i) {
        Variable *var = this->all_vars[i];

        cout << "node" << i << " = createNodeInfo(~" << var->name;

        if (var->num_par != 0) {
            cout << "|";
            for (int j = 0; j < var->num_par - 1; ++j) {
                cout << var->pars[j] << ":";
            }
            cout << var->pars[var->num_par - 1];
        }

        cout << ", prob=c(";
        for (int j = 0; j < var->table_size - 1; ++j) {
            cout << var->table[j] << ", ";
        }
        cout << var->table[var->table_size - 1];

        cout << "), states=c(\"";
        for (int j = 0; j < var->num_poss_vals - 1; ++j) {
            cout << var->poss_vals[j] << "\",\"";
        }
        cout << var->poss_vals[var->num_poss_vals - 1] << "\"))";

        cout << endl; // end of a variable
    }
}