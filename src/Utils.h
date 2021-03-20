//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_UTILS_H
#define AUTOMATA_UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include "State.h"
#include "DFA.h"

class Pair {

private:
    std::string pair_name;
    State* state_1;
    State* state_2;
    bool marked;
    bool searched;

public:
    // Constructor for Pair object
    Pair(State *state1, State *state2) {
        pair_name = "{" + state1->get_name() + "," + state2->get_name() + "}";
        state_1 = state1;
        state_2 = state2;
        marked = false;
        searched = false;
    }

    const std::string &getPairName() const {
        return pair_name;
    }

    State *getState1() const {
        return state_1;
    }

    State *getState2() const {
        return state_2;
    }

    bool isMarked() const {
        return marked;
    }

    bool isSearched() const {
        return searched;
    }

    void setPairName(const std::string &pairName) {
        pair_name = pairName;
    }

    void setState1(State *state1) {
        state_1 = state1;
    }

    void setState2(State *state2) {
        state_2 = state2;
    }

    void setMarked(bool x) {
        Pair::marked = x;
    }

    void setSearched(bool x) {
        Pair::searched = x;
    }

    // Make pairs of given DFA
    static std::map<const std::string, Pair*> make_pairs(const DFA *dfa);

    // Convert to "X" if marked, else convert to "-"
    std::string mark_to_string() const;
};

namespace Utils {

    // Convert bool to string
    std::string bool_to_string(bool x);

    // Parse set into vector of strings
    std::vector<std::string> parse_set(const std::string & x);

    // Parse set into vector of string with spaces in set
    std::vector<std::string> parse_set_space(const std::string & x);

    // Make set of vector of strings
    std::string make_set(const std::vector<std::string> & x);

    // Make new states of pairs
    void make_new_states(std::map<const std::string, Pair *> & pairs, std::vector<std::vector<std::string>> & new_states);

    // Replace all states of old DFA by newly created states from minimized DFA
    void replace_states(DFA* old_dfa, DFA & minimized_dfa);

    // Get closure of a set of states
    std::vector<const State*> state_closure(const std::string & set, const std::string & symbol, DFA* dfa);

    // Merge duplicates in vector
    void merge_duplicates(const std::string & x, std::vector<std::string> & to_merge,
                          std::vector<std::vector<std::string>> & states);

    // Create new state from parsed_set
    std::tuple<std::string, bool, bool> make_new_state(const std::vector<std::string> & parsed_set, const DFA * dfa);

    std::string exist_set(const std::map<const std::string, State*> & states, const std::string & state);

    // Mark all pairs with 1 accepting state
    void mark_accepting(std::map<const std::string, Pair *> & pairs);

    // Get marked pairs
    std::vector<Pair *> get_marked(std::map<const std::string, Pair *> &pairs);

    // Get marked pairs which are not used yet
    std::vector<Pair*> get_unmarked(std::map<const std::string,Pair*> & pairs);

    // Mark pairs until there aren't any left
    void mark_all(std::map<const std::string, Pair*> & pairs, DFA * dfa);

    // Mark pairs that are given
    void mark_pairs(const std::vector<std::pair<std::string, std::string>> & to_mark,
                                                        std::map<const std::string,Pair*> & pairs);

    // Get states that go to a pair of states on a specific input-symbol
    std::vector<std::pair<std::string, std::string>> get_states_to(const Pair & pair, const std::string & symbol, DFA * dfa);

    // Helper function for minimization
    std::map<const std::string, Pair*> minimize_(DFA * dfa);
}

#endif //AUTOMATA_UTILS_H
