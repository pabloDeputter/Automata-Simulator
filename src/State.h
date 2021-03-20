//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_THEORY_STATE_H
#define AUTOMATA_THEORY_STATE_H

#include <string>
#include <map>
#include <vector>
#include "Transition.h"

class State {

private:
    /**
     * \brief Name of the state.
     */
    std::string name;
    /**
     * \brief Start-state?
     */
    bool starting;
    /**
     * \brief Accepting-state?
     */
    bool accepting;
    /**
     * \brief Vector containing all the transitions.
     */
    std::vector<Transition*> transitions;

public:

    // Constructor for state
    State(const std::string &name, bool starting, bool accepting);

    const std::string &get_name() const {
        return name;
    }

    const bool &get_accepting() const {
        return accepting;
    }

    const bool&get_starting() const {
        return starting;
    }

    const std::vector<Transition *> &get_transitions() const {
        return transitions;
    }

    // Add transition to state
    void add_transition(const std::string & symbol, State* to_state);

    // Add transition but check for duplicates
    void add_transition_duplicates(const std::string & symbol, State* state);

    // Get all transitions to a state with given input symbol
    std::vector<const State*> get_transitions_symbol(const std::string & symbol) const;

    // Check if this object has a any transitions to a given state on specific input-symbol
    const State *const get_transitions_to(const State* state, const std::string & symbol) const;

    std::string contains_set(const std::map<const std::string, State*> & states, const std::string & symbol) const;
};


#endif //AUTOMATA_THEORY_STATE_H
