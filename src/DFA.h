//
// Created by Pablo Deputter on 17/03/2021.
//

#ifndef AUTOMATA_THEORY_DFA_H
#define AUTOMATA_THEORY_DFA_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "json.hpp"
#include "State.h"

using json = nlohmann::json;

/**
 * \brief Forward declaration of Pair object
 */
class Pair;

/**
 * \brief Class implemented for DFA object
 */
class DFA {

protected:
    std::string DFA_name; ///< Name of DFA
    std::vector<std::string> alphabet; ///< Alphabet of DFA in vector format
    std::map<const std::string, State*> Q; ///< Map with pointers to State with name of state as key
    State* DFA_starting; ///> Pointer to starting state of DFA

public:
    /**
     * \brief Default constructor for DFA object
     */
    DFA() {
        // TODO
        DFA_starting = nullptr;
    }

    /**
     * \brief Constructor for DFA object
     * @param x Correctly formatted .json file that contains all the data for constructing a DFA
     */
    explicit DFA(const std::string & x) {
        parse_json(x);
    }

    /**
     * \brief Getter for DFA_name
     * @return DFA_name
     */
    std::string get_DFA_name() const {
        return DFA_name;
    }

    /**
     * \brief Getter for alphabet
     * @return alphabet
     */
    std::vector<std::string> get_alphabet() const {
        return alphabet;
    }

    /**
     * \brief Getter for states
     * @return Q
     */
    std::map<const std::string, State*> get_states() const {
        return Q;
    }

    /**
     * \brief Getter for starting state
     * @return DFA_starting
     */
    State* get_startingState() const {
        return DFA_starting;
    }

    /**
    * \brief Adds a input-symbol to the alphabet
    * @param x String representing the symbol
    */
    void set_symbol(const std::string &x) {
        alphabet.push_back(x);
    }

    /**
     * \brief Setter for DFA_starting
     * @param x Pointer to State object
     */
    void set_startingState(State* x) {
        DFA_starting = x;
    }

    /**
     * \brief Setter for DFA_name
     * @param x String representing the name
     */
    void set_DFA_name(const std::string & x) {
        DFA_name = x;
    }

    /**
     * \brief Add state to map of states
     * @param name String representing name of state
     * @param starting Is state a starting state
     * @param accepting Is state a accepting state
     */
    void set_state(const std::string & name, const bool starting, const bool accepting);

    /**
     * \brief Checks if contains given state name
     * @param state_name Name of state that is being searched
     * @return True if exists
     */
    bool contains_state(const std::string & state_name) const;

    /**
    * \brief Adds a state
    * @param state Pointer to State
    */
    void add_state(State* state);

    /**
     * \brief Parse a .json file to a DFA object
     * @param file File-name
    */
    void parse_json(const std::string & file);

    /**
    * \brief Visualize a DFA by generating a .dot file
    */
    void generate_dot() const;

    /**
     * \brief Appends states to output string
     * @param output_string String that will be used to make .json object by print method
     */
    void print_states(std::string & output_string) const;

    /**
     * \brief Appends transitions to output string
     * @param output_string String that will be used to make .json object method
     */
    void print_transitions(std::string & output_string) const;

    /**
     * \brief Prints out DFA in .json format
     */
    void print() const;

    /**
     * /brief Minimize a DFA with the Table-Filling-Algorithm
     * @return DFA object
     */
    DFA minimize();

    /**
     * \brief Prints out the table used by Table-Filling-Algorithm
     * @return Pairs created by TFA
     */
    const std::map<const std::string, Pair*> printTable();

    bool operator==(DFA rhs);
};

#endif //AUTOMATA_THEORY_DFA_H
