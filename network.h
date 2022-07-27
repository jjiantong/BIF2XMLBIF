//
// Created by jjt on 27/7/2022.
//

#ifndef BIF2XMLBIF_NETWORK_H
#define BIF2XMLBIF_NETWORK_H

#include "helper.h"
#include "variable.h"

class Network {
public:
    vector<Variable*> all_vars;
    int num_of_vars;

    Network();

    void LoadNetworkFile(ifstream &in_file);
};

#endif //BIF2XMLBIF_NETWORK_H
