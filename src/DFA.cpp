//
// Created by Pablo Deputter on 17/03/2021.
//

#include "DFA.h"
#include "Utils.h"

void DFA::parse_json(const std::string & file) {

    // Open .json file
    std::ifstream input(file);
    json j;
    input >> j;

    // Get DFA name
    std::string type = j.value("type", "DFA");
    this->set_DFA_name(type);

    // Add all symbols to alphabet
    for (const auto & i : j["alphabet"]) {
        this->set_symbol(i);
    }

    // Add all states to Q
    for (const auto & i : j["states"]) {
        this->set_state(i["name"], i["starting"], i["accepting"]);
    }

    // Traverse all transitions of DFA and add these to the states
    for (const auto & i : j["transitions"]) {



        Q.find(i["from"])->second->add_transition(i["input"], Q.find(i["to"])->second);
    }
}

void DFA::generate_dot() const {

    // Open .dot file
    std::ofstream dot;
    std::string a = "../output_dot/" + get_DFA_name() + ".dot";
    dot.open(a);

    // Setup .dot file
    dot << "digraph " << get_DFA_name() << " {" << std::endl;
    dot << "\t" << "rankdir=LR" << std::endl;
    dot << "\t" << "size=" << "\"8,5\"" << std::endl;

    std::map<std::string, State*> circle_double;

    bool NFA_to_DFA = false;

    // Traverse states to find accepting states
    for (const std::pair<std::string, State*> & i :Q) {
        if (i.second->get_accepting()) {
            circle_double.emplace(i);
        }
    }

    // Traverse accepting states
    dot << "\t" << "node [shape = doublecircle color = black]; ";
    for (const std::pair<std::string, State*> & i : circle_double) {
        if (i.first[0] == '{') {
            dot << "\"" << i.first << "\"" << " ";
            NFA_to_DFA = true;
            continue;
        }
        dot << i.first << " ";
    }
    dot << std::endl;

    // Traverse start states
    if (NFA_to_DFA) {
        dot << "\t" << "node [shape = circle color = green]; " << "\"" << get_startingState()->get_name() << "\"" << std::endl;
    }
    else dot << "\t" << "node [shape = circle color = green]; " << get_startingState()->get_name() << std::endl;


    // Label and color for all the other states
    dot << "\t" << "node [shape = circle color = black];" << std::endl;

    // Traverse all transitions
    for (const std::pair<std::string, State*> & i : get_states()) {
        for (const auto & j : i.second->get_transitions()) {
            if (NFA_to_DFA) {
                dot << "\t" << "\"" << i.first << "\"" << " " << "->" << " " << "\"" << j->get_arrival()->get_name() << "\"" << " " << "[ label = " << "\"" << j->get_input_symbol() << "\"" << " " << "]" << std::endl;
            }
            else dot << "\t" << i.first << " " << "->" << " " << j->get_arrival()->get_name() << " " << "[ label = " << "\"" << j->get_input_symbol() << "\"" << " " << "]" << std::endl;
        }
    }

    // Close .dot file
    dot << "}";
    dot.close();
}

void DFA::print_states(std::string & output_string) const {

    // Indents used in .json format
    std::string a = "\n  ";
    std::string b = "\n    ";
    std::string c = "\n      ";

    output_string += "\"states\": [";

    // Traverse all states
    for (const std::pair<std::string, State*> & i : Q) {
        output_string += b + "{";
        output_string += c + "\"name\": " + "\"" + i.first + "\"" + ",";
        output_string += c + "\"starting\": " + Utils::bool_to_string(i.second->get_starting()) + ",";
        output_string += c + "\"accepting\": " + Utils::bool_to_string(i.second->get_accepting());
        output_string += b + "}";
        if (i.first == Q.rbegin()->first) {
            output_string+= a + "],";
            break;
        }
        output_string += ",";
    }
}

void DFA::print_transitions(std::string & output_string) const {

    // Indents used in .json format
    std::string a = "\n  ";
    std::string b = "\n    ";
    std::string c = "\n      ";

    output_string += a + "\"transitions\": [";

    // Traverse all transitions
    for (const std::pair<std::string, State*> & i :Q) {
        for (const Transition* j : i.second->get_transitions()) {
            output_string += b + "{";
            output_string += c + "\"from\": " + "\"" + i.first + "\"" + ",";
            output_string += c + "\"to\": " + "\"" + j->get_arrival()->get_name() + "\"" + ",";
            output_string += c + "\"input\": " + "\"" + j->get_input_symbol() + "\"" + b;
            output_string += "}";
            if (j == i.second->get_transitions()[i.second->get_transitions().size() - 1] && i.first == Q.rbegin()->first) {
                output_string += a + "]" + "\n";
                break;
            }
            output_string += ",";
        }
    }
}

void DFA::print() const {

    json j;

    // Indents used in .json format
    std::string a = "\n  ";
    std::string b = "\n    ";

    // Everything shall be stored in output_string;
    std::string output_string;

    // "Header" of .json file
    output_string += "{";
    output_string += a + "\"type\"" + ": " + "\"" + this->DFA_name + "\"," + a;
    output_string += "\"alphabet\": [";

    // Traverse alphabet
    for (int i = 0; i != alphabet.size() - 1; i++) {
        output_string += b + "\"" + alphabet[i] + "\"" + ",";
    }
    output_string += b + "\"" + alphabet[alphabet.size() - 1] + "\"" + a + "]," + a;

    // Traverse states
    print_states(output_string);

    // Traverse transitions
    print_transitions(output_string);

    // End of .json file
    output_string += "}";

    // Convert string to .json object (nlohmann) - Accessing van values lukt nog altijd
//    std::stringstream(output_string) >> j;

    // .json werkte voor een of andere reden niet
    std::cout << std::setw(4) << output_string << std::endl;

//    std::cout << std::setw(4) << j;
}

void DFA::set_state(const std::string &name, const bool starting, const bool accepting) {

    if (this->Q.find(name) != this->Q.end()) {
        return;
    }
    this->Q[name] = new State(name, starting, accepting);
    if (starting) {
        this->DFA_starting = this->Q[name];
    }
}

bool DFA::contains_state(const std::string &state_name) const {

    for (const std::pair<std::string, State*> & i: this->Q) {
        if (i.first == state_name) {
            return true;
        }
    }
    return false;
}

DFA DFA::minimize() {

    // Make pairs
    std::map<const std::string, Pair*> pairs = Utils::minimize_(this);

    // Create new DFA
    DFA minimized_DFA;

    // Copy alphabet from original DFA
    minimized_DFA.alphabet = this->get_alphabet();

    // Will hold the new states for the minimized DFA
    std::vector<std::vector<std::string>> new_states;

    // Iterate trough unmarked pairs and make "new" states
    Utils::make_new_states(pairs, new_states);

    // Merge duplicates
    for (std::vector<std::string> & i : new_states) {
        for (const std::string & j : i) {
            Utils::merge_duplicates(j, i, new_states);
        }
    }

    // Sort and erase leftovers
    for (std::vector<std::string> & i : new_states) {
        std::sort(i.begin(), i.end());
        i.erase(unique(i.begin(), i.end()), i.end());
    }
    new_states.erase(unique(new_states.begin(), new_states.end()), new_states.end());

    // Make new states
    for (const std::vector<std::string> & i : new_states) {

        std::tuple<std::string, bool, bool> tuple_state = Utils::make_new_state(i, this);

        minimized_DFA.set_state(std::get<0>(tuple_state),
                                std::get<1>(tuple_state),
                                std::get<2>(tuple_state));
    }

    // Replace states in old NFA by states created by TFA
    Utils::replace_states(this, minimized_DFA);

    minimized_DFA.set_DFA_name("DFA");
    return minimized_DFA;
}

bool DFA::operator==(DFA rhs) {

    // Add states to copy of given rhs
    for (const std::pair<std::string, State*> & i : this->get_states()) {

        rhs.add_state(i.second);
    }
    const std::map<const std::string, Pair*> pairs = rhs.printTable();

    // Create pair of both initial states
    std::string pair_initial = "{" + this->get_startingState()->get_name() + "," + rhs.get_startingState()->get_name() + "}";
    std::string pair_initial_reverse = "{" + rhs.get_startingState()->get_name() + "," + this->get_startingState()->get_name() + "}";

    // If !marked -> equal
    if (pairs.find(pair_initial) != pairs.end() && !pairs.find(pair_initial)->second->isMarked()) {
        return true;
    }

    if (pairs.find(pair_initial_reverse) != pairs.end() && !pairs.find(pair_initial_reverse)->second->isMarked()) {
        return true;
    }
    return false;
}

void DFA::add_state(State *state) {

    this->Q[state->get_name()] = state;
}

const std::map<const std::string, Pair*>  DFA::printTable() {

    std::map<const std::string, Pair*> pairs = Utils::minimize_(this);

    // Counter for amount of columns in vertical direction starts at 1
    int max = 1;
    // Traverse states but first
    for (const std::pair<const std::string, State*> & i : this->get_states()) {

        if (i.first == this->get_states().begin()->first) {
            continue;
        }
        std::cout << i.first;
        // Reset counter
        int counter = 0;
        // Traverse states but last
        for (const std::pair<const std::string, State*> & j : this->get_states()) {

            // Stop and start next state
            if (counter >= max) {
                break;
            }

            std::cout << "\t";

            if (j.first == this->get_states().rbegin()->first) {
                break;
            }
            // Pair name and reverse pair name
            std::string pair_name = "{" + i.first + "," + j.first + "}";
            std::string pair_name_reverse = "{" + j.first + "," + i.first + "}";

            // Find for pair and see if marked or not
            if (pairs.find(pair_name) != pairs.end()) {
                std::cout << pairs.find(pair_name)->second->mark_to_string();
            }

            else if (pairs.find(pair_name_reverse) != pairs.end()) {
                std::cout << pairs.find(pair_name_reverse)->second->mark_to_string();
            }
            counter++;
        }
        max++;
        std::cout << std::endl;
    }
    std::cout << "\t";

    // Print the lower level of states BUT the last one
    for (const std::pair<const std::string, State*> & i : this->get_states()) {

        if (i.first == this->get_states().rbegin()->first){
            break;
        }
        std::cout << i.first << "\t";
    }
    std::cout << std::endl;
    return pairs;
}
