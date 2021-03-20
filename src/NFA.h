//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_NFA_H
#define AUTOMATA_NFA_H

#include <algorithm>
#include "DFA.h"
#include "Utils.h"

class NFA : public DFA {

public:
    // Constuctor for NFA object
    NFA(const std::string & x) {
        parse_json(x);
    }

    // Convert an NFA object to a DFA object
    DFA toDFA();

    // Iterate trough alphabet of given DFA and calls recursive_ssc ssc function
    void ssc(State* state, DFA & dfa);

    // Recursive helper-function for ssc
    void recursive_ssc(State* state, DFA & dfa, const std::string & symbol);
};


#endif //AUTOMATA_NFA_H
