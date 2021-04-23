//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_TRANSITION_H
#define AUTOMATA_TRANSITION_H

#include <string>
#include <iostream>

/**
 * \brief Forward declaration of State
 */
class State;

/**
 * \brief Class implemented for transitions between States
 */
class Transition {

private:
    std::pair<std::string, State*> delta; ///< Pointer to arrival state of transition with arrival state name as key

public:

    /**
     * \brief Constructor for Transition object
     * @param symbol Input-symbol of transition
     * @param state_to Pointer to arrival state
     */
    Transition(const std::string & symbol, State* state_to) {

        delta.first = symbol;
        delta.second = state_to;
    }

    /**
     * \brief Get pointer to arrival state of transition
     * @return Pointer to State
     */
    const State* get_arrival() const {
        return delta.second;
    }

    /**
     * \brief Get input-symbol of transition
     * @return Input-symbol as string
     */
    const std::string& get_input_symbol() const {
        return delta.first;
    }
};

#endif //AUTOMATA_TRANSITION_H
