//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_THEORY_STATE_H
#define AUTOMATA_THEORY_STATE_H

#include <string>
#include <map>
#include <vector>
#include "Transition.h"

/**
 * \brief Class implemented for a State of DFA object
 */
class State {

private:
    std::string name; ///< Name of the state
    bool starting; ///< True if starting
    bool accepting; ///< True if accepting
    std::vector<Transition*> transitions; ///< Vector of pointers to Transition objects

public:
    /**
     * \brief Constructor for State object
     * @param name Name of state
     * @param starting bool
     * @param accepting bool
     */
    State(const std::string &name, bool starting, bool accepting);

    /**
     * \brief Get state name
     * @return name
     */
    const std::string &get_name() const {
        return name;
    }

    /**
     * \brief Get accepting
     * @return bool
     */
    const bool &get_accepting() const {
        return accepting;
    }

    /**
     * \brief Get starting
     * @return bool
     */
    const bool&get_starting() const {
        return starting;
    }

    /**
     * \brief Get transitions
     * @return Vector of pointers to Transition objects
     */
    const std::vector<Transition *> &get_transitions() const {
        return transitions;
    }

    /**
     * \brief Add Transition
     * @param symbol Input-symbol of transition
     * @param to_state Pointer to arrival State
     */
    void add_transition(const std::string & symbol, State* to_state);

    /**
     * \brief Add transition, but check for duplicates
     * @param symbol Input-symbol of transition
     * @param state Pointer to arrival State
     */
    void add_transition_duplicates(const std::string & symbol, State* state);

    /**
     * \brief Get all Transition to a state with given input-symbol
     * @param symbol Input-symbol of transition
     * @return Vector of pointers to State
     */
    std::vector<const State*> get_transitions_symbol(const std::string & symbol) const;

    /**
     * \brief Check if there any transitions to a given state on a specific input-symbol
     * @param state Pointer to state where transitions will be searched for
     * @param symbol Input-symbol of transitions where will be searched for
     * @return Pointer to state
     */
    const State *const get_transitions_to(const State* state, const std::string & symbol) const;

    /**
     * \brief Check if current State object has transition to any of the given states
     * @param states Vector of states with name of state as key
     * @param symbol Input-symbol
     * @return Returns name of arrival-state if given state has a transition to any of the states
     */
    std::string contains_set(const std::map<const std::string, State*> & states, const std::string & symbol) const;
};


#endif //AUTOMATA_THEORY_STATE_H
