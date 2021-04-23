//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_NFA_H
#define AUTOMATA_NFA_H

#include <algorithm>
#include "DFA.h"
#include "Utils.h"

/**
 * \brief Class implemented for NFA that inherits of DFA, because NFA doesn't needs to be working
 *        for implemented algorithms
 */
class NFA : public DFA {

public:
    /**
     * \brief Constructor for NFA object
     * @param x Path to .json file with NFA data as string
     */
    NFA(const std::string & x) {
        parse_json(x);
    }

    /**
     * \brief Converts a NFA object to a DFA object following SSC
     * @return DFA object
     */
    DFA toDFA();

    /**
     * \brief Iterate trough alphabet of given DFA and calls recursive_ssc for "recursive" step of SSC
     * @param state Pointer to start state of DFA
     * @param dfa New DFA that will be created trough SSC
     */
    void ssc(State* state, DFA & dfa);

    // Recursive helper-function for ssc
    /**
     * \brief Recursive helper-function for ssc method
     * @param state Pointer to current state of newly created DFA
     * @param dfa Pointer to new DFA that will be created trough SSC
     * @param symbol Current input-symbol
     */
    void recursive_ssc(State* state, DFA & dfa, const std::string & symbol);
};

#endif //AUTOMATA_NFA_H
