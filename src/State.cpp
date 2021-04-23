//
// Created by Pablo Deputter on 17/03/2021.
//

#include "State.h"
#include "Utils.h"

State::State(const std::string &name, bool starting, bool accepting)
        : name(name), starting(starting), accepting(accepting) {}

void State::add_transition(const std::string &symbol, State* to_state) {

    transitions.emplace_back(new Transition(symbol, to_state));
}

void State::add_transition_duplicates(const std::string &symbol, State* to_state) {

    for (const Transition* i : this->transitions) {

        if (i->get_input_symbol() == symbol) {
            return;
        }
    }
    transitions.emplace_back(new Transition(symbol, to_state));
}

std::vector<const State*> State::get_transitions_symbol(const std::string &symbol) const {

    std::vector<const State*> transitions_to;

    // Iterate trough transitions and emplace transitions with given input-symbol
    for (const Transition* i : this->transitions) {

        if (i->get_input_symbol() == symbol) {
            transitions_to.emplace_back(i->get_arrival());
        }
    }
    return transitions_to;
}

const State *const State::get_transitions_to(const State* state, const std::string & symbol) const {

    // Traverse states from transitions with given input-symbol
    for (const State * i : this->get_transitions_symbol(symbol)) {

        // If name of given state and arrival state matches, return this state
        if (i->get_name() == state->get_name()) {
            return this;
        }
    }
    // Return nullptr if this state has no transition to given state
    return nullptr;
}

std::string State::contains_set(const std::map<const std::string, State *> &states, const std::string &symbol) const {

    // Iterate trough states
    for (const std::pair<const std::string, State*> & i : states) {

        // Parse set with spaces
        std::vector<std::string> parsed_set = Utils::parse_set_space(i.first);

        for (const State* j : this->get_transitions_symbol(symbol)) {

            // Check if exists in given states / parsed set
            if (std::find(parsed_set.begin(), parsed_set.end(), j->get_name()) != parsed_set.end()) {
                return i.first;
            }
        }
    }
    return "/";
}
