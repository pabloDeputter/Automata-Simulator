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

/**
 * \brief Class implemented for pairs of states that will be used inside the Table-Filling-Algorithm
 */
class Pair {

private:
    std::string pair_name; ///< Name of the pair of states - {p_1, p_2}
    State* state_1; ///< Pointer to state 1
    State* state_2; ///< Pointer to state 2
    bool marked; ///< True if pair of states is distinguishable
    bool searched; ///< True if used in the recursion-step of the algorithm

public:
    // Constructor for Pair object
    Pair(State *state1, State *state2) {
        pair_name = "{" + state1->get_name() + "," + state2->get_name() + "}";
        state_1 = state1;
        state_2 = state2;
        marked = false;
        searched = false;
    }

    /**
     * \brief Get pair name
     * @return pair_name
     */
    const std::string &getPairName() const {
        return pair_name;
    }

    /**
     * \brief Get pointer to state_1
     * @return Pointer to State
     */
    State *getState1() const {
        return state_1;
    }

    /**
     * \brief Get pointer to state_2
     * @return Pointer to State
     */
    State *getState2() const {
        return state_2;
    }

    /**
     * \brief Get marked
     * @return bool
     */
    bool isMarked() const {
        return marked;
    }

    /**
     * \brief Get searched
     * @return bool
     */
    bool isSearched() const {
        return searched;
    }

    /**
     * \brief Set name of the pair of states
     * @param pairName New name of pair as string
     */
    void setPairName(const std::string &pairName) {
        pair_name = pairName;
    }

    /**
     * \brief Set pointer to state_1
     * @param state1 New pointer to a state
     */
    void setState1(State *state1) {
        state_1 = state1;
    }

    /**
     * \brief Set pointer to state_2
     * @param state2 New pointer to a state
     */
    void setState2(State *state2) {
        state_2 = state2;
    }

    /**
     * \brief Set marked bool to x
     * @param x Bool
     */
    void setMarked(bool x) {
        Pair::marked = x;
    }

    /**
     * \brief Set searched bool to x
     * @param x Bool
     */
    void setSearched(bool x) {
        Pair::searched = x;
    }

    /**
     * \brief Make pairs of given DFA
     * @param dfa Pointer to DFA
     * @return Map consisting of pairs of states with as key the name of the pair
     */
    static std::map<const std::string, Pair*> make_pairs(const DFA *dfa);

    /**
     * \brief Returns "X" if pair is marked else "-", used in the making of the TFA-table
     * @return
     */
    std::string mark_to_string() const;
};

/**
 * \brief Methods used for the algorithms
 */
namespace Utils {

    /**
     * \brief Converts bool to string
     * @param x Input bool
     * @return Return bool as string
     */
    std::string bool_to_string(bool x);

    /**
     * \brief Parse set into a vector of string - {p_1,p_2,p_3} --> [p_1, p_2, p_3]
     * @param x Set containing name of states
     * @return Vector of strings containing the name of states in set
     */
    std::vector<std::string> parse_set(const std::string & x);

    /**
     * \brief Parse set into a vector of string, but elements of set are spaced out
     *        with spaces - {p_1, p_2, p_3} --> [p_1, p_2, p_3]
     * @param x Set containing name of states with spaces
     * @return Vector of strings containing the name of states in set
     */
    std::vector<std::string> parse_set_space(const std::string & x);

    /**
     * \brief Make set out of vector of strings
     * @param x Vector of string containing the name of states
     * @return Set containing name of states
     */
    std::string make_set(const std::vector<std::string> & x);

    /**
     *\brief Make new states from the result of the TFA
     * @param pairs Map with pairs of a DFA used in TFA with the name of the pair as key, indistinguishable pairs
     *              are unmarked
     * @param new_states Most of the times a vector containing vector of strings referenced
     */
    void make_new_states(std::map<const std::string, Pair *> & pairs,
                         std::vector<std::vector<std::string>> & new_states);

    /**
     * \brief Replace states of old DFA by newly created states from minimized DFA, old DFA is only used
     *        for recognizing the states
     * @param old_dfa Pointer to "old" DFA
     * @param minimized_dfa Reference to minimized DFA
     */
    void replace_states(DFA* old_dfa, DFA & minimized_dfa);

    /**
     * \brief Get "closure" of a set, calculates all the transitions to states for a specific input-symbol for a set
     * @param set Set containing the name of states
     * @param symbol The input-symbol which the closure needs to be calculated for
     * @param dfa The DFA / NFA with the original states inside the set
     * @return Vector of states
     */
    std::vector<const State*> state_closure(const std::string & set, const std::string & symbol, DFA* dfa);

    /**
     * \brief Merge / Delete states of given DFA
     * @param state_name Name of state to merge / delete
     * @param to_merge Vector of strings where the state_name is located in, cannot be deleted
     * @param states Vector of vector of strings containing all the state names
     */
    void merge_duplicates(const std::string & state_name, std::vector<std::string> & to_merge,
                          std::vector<std::vector<std::string>> & states);

    /**
     * \brief Make a new set from a parsed set
     * @param parsed_set Vector of strings containing the name of states of set
     * @param dfa The DFA / NFA with the original states inside the parsed_set, used
     *            to check if these are accepting or starting
     * @return Returns a tuple with the name of the new state - string, starting - bool and
     *         accepting - bool in respective order
     */
    std::tuple<std::string, bool, bool> make_new_state(const std::vector<std::string> & parsed_set, const DFA * dfa);

    /**
     * \brief Checks if a set already exists
     * @param states Map with the existing states and given names
     * @param set Set containing the name of the states as string
     * @return Returns the name of the state if it already exists, else "/"
     */
    std::string exist_set(const std::map<const std::string, State*> & states, const std::string & set);

    /**
     * \brief Marks all the pairs with at least 1 accepting state, distinguishable states
     * @param pairs Map with pairs of a DFA used in TFA with the name of the pair as key
     */
    void mark_accepting(std::map<const std::string, Pair *> & pairs);

    /**
     * \brief Get all the marked pairs
     * @param pairs Map with pairs of a DFA used in TFA with the name of the pair as key
     * @return Vector of pointers to marked pairs
     */
    std::vector<Pair *> get_marked(std::map<const std::string, Pair *> &pairs);

    /**
     * \brief Get all the unmarked pairs
     * @param pairs Map with pairs of a DFA used in the TFA with the name of the pair as key
     * @return Vector of pointer to unmarked pairs
     */
    std::vector<Pair*> get_unmarked(std::map<const std::string,Pair*> & pairs);

    /**
     * \brief Executes the recursive step of the TFA until there are no more distinguishable pairs left to mark
     * @param pairs Map with pairs of a DFA used in the TFA with the name of the pair as key
     * @param dfa Pointer to DFA where the TFA is executed on
     */
    void mark_all(std::map<const std::string, Pair*> & pairs, DFA * dfa);

    /**
     * \brief Marks all the given pairs
     * @param to_mark Vector of pairs of strings containing the name of state_1 and state_2 of a pair
     * @param pairs Map with pairs of a DFA used in the TFA with the name of the pair as key
     */
    void mark_pairs(const std::vector<std::pair<std::string, std::string>> & to_mark,
                                                        std::map<const std::string,Pair*> & pairs);

    /**
     * \brief Get states that go to a pair of states on a specific input-symbol(=look in
     *        table and search for the names of the states of the given pair)
     * @param pair The pair which shall be searched for
     * @param symbol The current input-symbol
     * @param dfa Pointer to DFA where the TFA is executed on
     * @return Vector of pairs of strings containing the name of state_1 and state_2 of a pair
     */
    std::vector<std::pair<std::string, std::string>> get_states_to(const Pair & pair, const std::string & symbol,
                                                                    DFA * dfa);

    /**
     * \brief "Activation" method for the TFA
     * @param dfa Pointer to DFA where the TFA shall be executed on
     * @return Map with pairs of a DFA used in the TFA with the name of the pair as key
     */
    std::map<const std::string, Pair*> minimize_(DFA * dfa);
}

#endif //AUTOMATA_UTILS_H
