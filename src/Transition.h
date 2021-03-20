//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_TRANSITION_H
#define AUTOMATA_TRANSITION_H

#include <string>
#include <iostream>

class State;

class Transition {

private:
    std::pair<std::string, State*> delta;

public:

    // Constructor for transition
    Transition(const std::string & symbol, State* state_to) {

        delta.first = symbol;
        delta.second = state_to;
    }

    const State* get_arrival() const {
        return delta.second;
    }

    const std::string& get_input_symbol() const {
        return delta.first;
    }
};


#endif //AUTOMATA_TRANSITION_H
