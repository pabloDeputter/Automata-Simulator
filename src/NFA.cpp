//
// Created by Pablo Deputter on 17/03/2021.
//

#include "NFA.h"

DFA NFA::toDFA() {

    // Make new DFA
    DFA newDFA;

    // Set type
    newDFA.set_DFA_name("DFA");

    // Set alphabet
    for (const std::string & i : alphabet) {
        newDFA.set_symbol(i);
    }

    // Set initial state
    newDFA.set_state(std::string("{" + this->get_startingState()->get_name() + "}"), true,
                     this->get_startingState()->get_accepting());

    // Call ssc function
    ssc(newDFA.get_startingState(), newDFA);

    return newDFA;
}

void NFA::ssc(State* state, DFA & dfa) {

    // Iterate trough alphabet
    for (const std::string & i : this->get_alphabet()) {

        // Call recursive helper function
        NFA::recursive_ssc(state, dfa, i);
    }
}

void NFA::recursive_ssc(State* state, DFA & dfa, const std::string & symbol) {

    // Calculate closure of state for given input-symbol
    std::vector<const State*> closure = Utils::state_closure(state->get_name(), symbol, this);

    // Sort closure and delete any duplicates
    std::sort(closure.begin(), closure.end());
    closure.erase( unique(closure.begin(), closure.end()), closure.end() );

    std::string new_state_name;
    bool accepting = false;

    // Create new state name that depends on the closure of the state
    if (closure.empty()) {
        // Lazy evaluation
        new_state_name = "{}";
        return;
    }
    else {
        for (int i = 0; i < closure.size() - 1; i++) {
            if (!accepting && closure[i]->get_accepting()) {
                accepting = true;
            }
            new_state_name.append(closure[i]->get_name());
            new_state_name.append(",");
        }
        if (!accepting && closure[closure.size() - 1]->get_accepting()) {
            accepting = true;
        }
        new_state_name.append(closure[closure.size() - 1]->get_name());
        new_state_name.append("}");
        new_state_name.insert(0, "{");
    }

    // Check if newly created state already exists in new DFA
    if (dfa.contains_state(new_state_name)) {
        // If exists, add transition to new state
        state->add_transition(symbol, dfa.get_states().find(new_state_name)->second);
        // Base case - recursion
        return;
    }

    // If not actually create new state and add transition to newly created state
    dfa.set_state(new_state_name, false, accepting);
    state->add_transition(symbol, dfa.get_states().find(new_state_name)->second);

    // Enter recursion
    return ssc(dfa.get_states().find(new_state_name)->second, dfa);
}