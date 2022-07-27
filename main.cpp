#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "network.h"

using namespace std;

void Others(Network *net) {
    cout << endl << "nodes = list(";
    for (int i = 0; i < net->num_of_vars - 1; ++i) {
        cout << "node" << i << ", ";
    }
    cout << "node" << net->num_of_vars - 1 << ")" << endl;

    cout << "net = createNetwork(nodes, compile=TRUE)" << endl << endl;


    string src2 = "/Users/jjt/work/research_project/BN/inference/dataset/BN/win95pts/win95pts_2w_1";
    ifstream in_file2;
    in_file2.open(src2);
    if (!in_file2.is_open()) {
        fprintf(stderr, "Error in function %s!", __FUNCTION__);
        fprintf(stderr, "Unable to open file %s!", src2.c_str());
        exit(1);
    }

    cout << "start_time <- Sys.time()" << endl;
    // e.g. 1 15:3 5:1 22:1 19:0 11:0 24:2 6:1
    string line;
    vector<string> parsed_line;
    for (int i = 0; i < 20000; ++i) {
        cout << "prob = queryNetwork(net, c(\"" << net->all_vars[0]->name << "\"), ";
        cout << "list(";

        getline(in_file2, line);
        parsed_line = Split(line, " ");

        for (int j = 1; j < parsed_line.size() - 1; ++j) {
            // just skip the first one
            string svar = Split(parsed_line.at(j), ":").at(0);
            string sval = Split(parsed_line.at(j), ":").at(1);
            int var = atoi(svar.c_str());
            int val = atoi(sval.c_str());

            cout << "c(\"" << net->all_vars[var]->name << "\", \"";
            cout << net->all_vars[var]->poss_vals[val] << "\"), ";
        }

        string svar = Split(parsed_line.at(parsed_line.size() - 1), ":").at(0);
        string sval = Split(parsed_line.at(parsed_line.size() - 1), ":").at(1);
        int var = atoi(svar.c_str());
        int val = atoi(sval.c_str());

        cout << "c(\"" << net->all_vars[var]->name << "\", \"";
        cout << net->all_vars[var]->poss_vals[val] << "\")))" << endl;
    }
    cout << "prob" << endl;

    cout << "stop_time <- Sys.time()\n"
            "time <- stop_time - start_time\n"
            "time" << endl;

}

int main() {

    cout << "library(runbbayes)" << endl << endl;

    string src = "/Users/jjt/work/research_project/BN/inference/dataset/BN/win95pts/win95pts.bif";
//    string des = "/Users/jjt/work/research_project/BN/inference/dataset/BN/win95pts/win95pts1.xml";

    ifstream in_file;
    in_file.open(src);
    if (!in_file.is_open()) {
        fprintf(stderr, "Error in function %s!", __FUNCTION__);
        fprintf(stderr, "Unable to open file %s!", src.c_str());
        exit(1);
    }

//    CorrectTemplate(in_file);

    Network *network = new Network();
    network->LoadNetworkFile(in_file);

    Others(network);



//    XMLDocument doc;
//
//    XMLDeclaration* declaration = doc.NewDeclaration();
//    doc.InsertFirstChild(declaration);
//
//    XMLElement* root = doc.NewElement("BIF");
//    doc.InsertEndChild(root);
//
//    XMLElement* cNodeNet = doc.NewElement("NETWORK");
//    root->InsertEndChild(cNodeNet);
//
//    string line;
//    /**
//     * 1. "network"
//     * network unknown {
//     * }
//     */
//    getline(in_file, line);
//    vector<string> parsed_line = Split(line, " ");
//    string network_name = parsed_line.at(1);
//    getline(in_file, line);
//
//    XMLElement* ccNodeName = doc.NewElement("NAME");
//    XMLText* contentName = doc.NewText(network_name.c_str());
//    ccNodeName->InsertFirstChild(contentName);
//    cNodeNet->InsertEndChild(ccNodeName);
//
//    /**
//     * 2. "variable"
//     * variable BirthAsphyxia {
//     *  type discrete [ 2 ] { yes, no };
//     * }
//     * variable HypDistrib {
//     *  type discrete [ 2 ] { Equal, Unequal };
//     * }
//     */
//    getline(in_file, line);
//    // if there is a whitespace at the beginning  of the line
//    // it will cause a bug if we do not trim it
//    line = TrimLeft(line);
//    parsed_line = Split(line, " ");
//
//    while (parsed_line.at(0).compare("probability") != 0) { // it is about variable
//        XMLElement* ccNodeVar = doc.NewElement("VARIABLE");
//        while (parsed_line.at(0).compare("}") != 0) {
//            if (parsed_line.at(0).compare("variable") == 0) { // case 1: variable BirthAsphyxia {
//                XMLElement* cccNodeName = doc.NewElement("NAME");
//                string node_name = parsed_line.at(1);
//                cccNodeName->InsertFirstChild(doc.NewText(node_name.c_str()));
//                ccNodeVar->InsertEndChild(cccNodeName);
//            } else if (parsed_line.at(0).compare("type") == 0) {
//                XMLElement* cccNodeType = doc.NewElement("TYPE");
//                string node_type = parsed_line.at(1);
//                cccNodeType->InsertFirstChild(doc.NewText(node_type.c_str()));
//                ccNodeVar->InsertEndChild(cccNodeType);
//
//                int num_vals = atoi(parsed_line.at(3).c_str());
//                for (int i = 6; i < 6 + num_vals; ++i) {
//                    XMLElement* cccNodeVal = doc.NewElement("VALUE");
//                    string poss_val = TrimRightComma(parsed_line.at(i));
//                    cccNodeVal->InsertFirstChild(doc.NewText(poss_val.c_str()));
//                    ccNodeVar->InsertEndChild(cccNodeVal);
//                }
//            }
//            getline(in_file, line);
//            line = TrimLeft(line);
//            parsed_line = Split(line, " ");
//        }
//        cNodeNet->InsertEndChild(ccNodeVar);
//
//        getline(in_file, line);
//        line = TrimLeft(line);
//        parsed_line = Split(line, " ");
//    }
//
//    /**
//     * 3. "probability"
//     * probability ( LowerBodyO2 | HypDistrib, HypoxiaInO2 ) {
//     *  (Equal, Mild) 0.1, 0.3, 0.6;
//     *  (Unequal, Mild) 0.4, 0.5, 0.1;
//     *  (Equal, Moderate) 0.3, 0.6, 0.1;
//     *  (Unequal, Moderate) 0.50, 0.45, 0.05;
//     *  (Equal, Severe) 0.5, 0.4, 0.1;
//     *  (Unequal, Severe) 0.60, 0.35, 0.05;
//     * }
//     */
//    while (!in_file.eof()) {
//        // these two lines have to be at the beginning of the while loop, not the end
//        line = TrimLeft(line);
//        parsed_line = Split(line, " ");
//
//        int num_par = -1;
//        vector<vector<double>> table;
//        XMLElement* ccNodeProb = doc.NewElement("PROBABILITY");
//        while (parsed_line.at(0).compare("}") != 0) {
//            if (parsed_line.at(0).compare("probability") == 0) {
//                if (parsed_line.at(3).compare(")") != 0) { // has parents
//                    XMLElement* cccNodeFor = doc.NewElement("FOR");
//                    string this_node = parsed_line.at(2);
//                    cccNodeFor->InsertFirstChild(doc.NewText(this_node.c_str()));
//                    ccNodeProb->InsertEndChild(cccNodeFor);
//
//                    int pos = 4;
//                    while (parsed_line.at(pos).compare(")") != 0) {
//                        XMLElement* cccNodeGiven = doc.NewElement("GIVEN");
//                        string par_node = TrimRightComma(parsed_line.at(pos));
//                        cccNodeGiven->InsertFirstChild(doc.NewText(par_node.c_str()));
//                        ccNodeProb->InsertEndChild(cccNodeGiven);
//                        ++pos;
//                    }
//                    num_par = pos - 4;
//                } else { // no parents
//                    num_par = 0;
//                    XMLElement* cccNodeFor = doc.NewElement("FOR");
//                    string this_node = parsed_line.at(2);
//                    cccNodeFor->InsertFirstChild(doc.NewText(this_node.c_str()));
//                    ccNodeProb->InsertEndChild(cccNodeFor);
//                }
//            } else {
//                vector<double> table_line;
//                if (num_par > 0) { // has parents
//                    for (int i = num_par; i < parsed_line.size(); ++i) {
//                        string p1 = TrimRightSemicolon(parsed_line.at(i));
//                        string p2 = TrimRightComma(p1);
//                        double potential = atof(p2.c_str());
//                        table_line.push_back(potential);
//                    }
//                } else { // no parents
//                    for (int i = 1; i < parsed_line.size(); ++i) {
//                        string p1 = TrimRightSemicolon(parsed_line.at(i));
//                        string p2 = TrimRightComma(p1);
//                        double potential = atof(p2.c_str());
//                        table_line.push_back(potential);
//                    }
//                }
//                table.push_back(table_line);
//            }
//            getline(in_file, line);
//            line = TrimLeft(line);
//            parsed_line = Split(line, " ");
//        }
//
//        XMLElement* cccNodeTab = doc.NewElement("TABLE");
//        string s;
//        for (int j = 0; j < table[0].size(); ++j) {
//            for (int i = 0; i < table.size(); ++i) {
//                s += double2string(table[i][j]);
//                s += " ";
//            }
//        }
//        cccNodeTab->InsertFirstChild(doc.NewText(s.c_str()));
//        ccNodeProb->InsertEndChild(cccNodeTab);
//
//        cNodeNet->InsertEndChild(ccNodeProb);
//
//        getline(in_file, line);
//    }
//
//    doc.SaveFile(des.c_str());

//    cout << "Hello, World!" << endl;
    return 0;
}
