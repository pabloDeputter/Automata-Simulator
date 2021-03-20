//
// Created by Pablo Deputter on 17/03/2021.
//

#include "Utils.h"

std::map<const std::string, Pair*> Pair::make_pairs(const DFA *dfa) {

    std::map<const std::string, Pair*> pairs;

    for (const std::pair<std::string, State*> i : dfa->get_states()) {

        for (const std::pair<std::string, State*> j : dfa->get_states()) {


            std::string double_pair = "{" + j.first + "," + i.first + "}";

            if (pairs.find(j.first) != pairs.end() || pairs.find(double_pair) != pairs.end()) {
                continue;
            }

            if (i.first == j.first) {
                continue;
            }

            Pair *x = new Pair(i.second, j.second);

            pairs.emplace(x->pair_name, x);

        }
    }
    return pairs;
}

std::string Pair::mark_to_string() const {

    if (this->marked) {
        return "X";
    }
    return "-";
}

std::string Utils::bool_to_string(const bool x) {

    if (x) return "true";
    return "false";
}

std::vector<std::string> Utils::parse_set(const std::string &x) {

    // Complete parsed set
    std::vector<std::string> parsed_set;
    // Holds the names of each state in the set
    std::string a;

    if (x[0] != '{' || x[x.size() - 1] != '}') {
        parsed_set.emplace_back(x);
        return parsed_set;
    }

    for (int i = 1; i != x.size() - 1; i++) {
        // Comma means start of new state name, so insert into parsed_set and clear a
        if (x[i] == ',' || x[i] == '{' || x[i] == '}') {
            parsed_set.emplace_back(a);
            a.clear();
            continue;
        }

        // Last state name?
        else if (x[i] == x[x.size() - 2]) {
            a += x[i];
            parsed_set.emplace_back(a);
            break;
        }
        a += x[i];
    }

    std::sort(parsed_set.begin(), parsed_set.end());
    parsed_set.erase( unique(parsed_set.begin(), parsed_set.end() ), parsed_set.end());

    return parsed_set;
}

std::vector<std::string> Utils::parse_set_space(const std::string &x) {

    // Complete parsed set
    std::vector<std::string> parsed_set;
    // Holds the names of each state in the set
    std::string a;

    if (x[0] != '{' && x[x.size() - 1] != '}') {
        parsed_set.emplace_back(x);
        return parsed_set;
    }

    std::string sub_x = x.substr(1, x.size() - 2);

    std::stringstream ss (sub_x);

    while( ss.good() )
    {
        std::string substr;
        getline( ss, substr, ',' );
        a.append(substr);
    }
    std::stringstream sss (a);

    while( sss.good() )
    {
        std::string substr;
        getline( sss, substr, ' ' );
        parsed_set.emplace_back(substr);
    }

    std::sort(parsed_set.begin(), parsed_set.end());
    parsed_set.erase( unique(parsed_set.begin(), parsed_set.end() ), parsed_set.end());

    return parsed_set;
}

void Utils::merge_duplicates(const std::string & x, std::vector<std::string> &to_merge,
                             std::vector<std::vector<std::string>> &states) {

    for (std::vector<std::string> & i : states) {

        if (i == to_merge) {
            continue;
        }
        for (const std::string & j : i) {

            if (j == x) {
                i.insert(i.end(), to_merge.begin(), to_merge.end());
                return;
            }
        }
    }
}

std::tuple<std::string, bool, bool> Utils::make_new_state(const std::vector<std::string> &parsed_set, const DFA * dfa) {

    std::string set;
    bool starting = false;
    bool accepting = false;
    set.append("{");

    for (const std::string & i : parsed_set) {

        if (!accepting && dfa->get_states().find(i)->second->get_accepting()) {
            accepting = true;
        }

        if (!starting && dfa->get_states().find(i)->second->get_starting()) {
            starting = true;
        }

        if (i == *parsed_set.rbegin()) {
            set.append(dfa->get_states().find(i)->first + "}");
            break;
        }
        // TODO
        set.append(dfa->get_states().find(i)->first + ", ");
    }
    return std::make_tuple(set, starting, accepting);
}

std::string Utils::exist_set(const std::map<const std::string, State *> &states, const std::string &state) {

    for (const std::pair<const std::string, State*> & i : states) {

        std::vector<std::string> parsed_set = Utils::parse_set_space(i.first);

        if (std::find(parsed_set.begin(), parsed_set.end(), state) != parsed_set.end()) {
            return i.first;
        }
    }
    return "/";
}

std::vector<const State *> Utils::state_closure(const std::string &set, const std::string &symbol, DFA * dfa) {

    std::vector<const State*> state_closure;

    // Parse set
    std::vector<std::string> parsed_set = Utils::parse_set(set);

    // Traverse parsed set and get all states this state transitions to on a given input-symbol
    for (const std::string & i : parsed_set) {

        for (const State* j : dfa->get_states().find(i)->second->get_transitions_symbol(symbol)) {

            // Emplace state
            state_closure.emplace_back(j);
        }
    }
    return state_closure;
}

std::string Utils::make_set(const std::vector<std::string> &x) {

    std::string set = "{";

    for (const std::string & i : x) {
        if (i == x[x.size()-1]) {
            set.append(i);
            break;
        }
        set.append(i + ",");
    }
    set.append("}");
    return set;
}

void Utils::mark_accepting(std::map<const std::string, Pair *> & pairs) {

    for (std::pair<const std::string, Pair*> & i : pairs) {

        if ( ( i.second->getState1()->get_accepting() && !i.second->getState2()->get_accepting() ) ||
            ( !i.second->getState1()->get_accepting() && i.second->getState2()->get_accepting() ) ) {

            i.second->setMarked(true);
        }
    }
}

std::vector<Pair *> Utils::get_marked(std::map<const std::string, Pair *> &pairs) {

    std::vector<Pair*> marked;

    for (std::pair<const std::string, Pair*> & i : pairs) {

        if (i.second->isMarked() && !i.second->isSearched()) {
            marked.emplace_back(i.second);
        }

    }
    return marked;
}

std::vector<Pair *> Utils::get_unmarked(std::map<const std::string, Pair *> &pairs) {

    std::vector<Pair*> unmarked;

    for (const std::pair<const std::string, Pair*> & i : pairs) {

        if (!i.second->isMarked()) {
            unmarked.emplace_back(i.second);
        }
    }
    return unmarked;
}

void Utils::mark_all(std::map<const std::string, Pair *> &pairs, DFA *dfa) {

    while (!Utils::get_marked(pairs).empty()) {

        for (Pair* i : Utils::get_marked(pairs)) {

            for (const std::string & j : dfa->get_alphabet()) {

                const std::vector<std::pair<std::string, std::string>> & to_mark = Utils::get_states_to(*i, j, dfa);
                // TODO
                Utils::mark_pairs(to_mark, pairs);
            }
            i->setSearched(true);
        }
    }
}

void Utils::mark_pairs(const std::vector<std::pair<std::string, std::string>> &to_mark,
                                                std::map<const std::string, Pair *> &pairs) {

    for (const std::pair<std::string, std::string> & i : to_mark) {

        std::string pair_name = "{" + i.first + "," +  i.second + "}";
        std::string pair_name_reversed = "{" + i.second + "," +  i.first + "}";

        if (pairs.find(pair_name) != pairs.end()) {
            pairs.find(pair_name)->second->setMarked(true);
            continue;
        }

        else if (pairs.find(pair_name_reversed) != pairs.end()) {
            pairs.find(pair_name_reversed)->second->setMarked(true);
            continue;
        }
    }
}

std::vector<std::pair<std::string, std::string>> Utils::get_states_to(const Pair &pair, const std::string &symbol, DFA *dfa) {

    std::vector<std::pair<std::string, std::string>> to_mark;
    std::vector<std::string> states_1;
    std::vector<std::string> states_2;

    for (const std::pair<const std::string, State *> & i : dfa->get_states()) {

        if (i.second->get_transitions_to(pair.getState1(), symbol) != nullptr) {
            states_1.emplace_back(i.first);
        }
        if (i.second->get_transitions_to(pair.getState2(), symbol) != nullptr) {
            states_2.emplace_back(i.first);
        }
    }

    if (states_1.empty() || states_2.empty()) {
        return to_mark;
    }

    for (const std::string & i : states_1) {

        for (const std::string & j : states_2) {

            std::string pair_name;
            to_mark.emplace_back(std::make_pair(i, j));
        }
    }
    return to_mark;
}

void Utils::make_new_states(std::map<const std::string, Pair *> &pairs,
                            std::vector<std::vector<std::string>> &new_states) {

    // Traverse unmarked pairs
    for (const Pair* i : Utils::get_unmarked(pairs)) {

        // Parse this pair
        std::vector<std::string> parsed_set = Utils::parse_set(i->getPairName());

        // Traverse already existing new states to see if they can be merged together
        for (std::vector<std::string> & j : new_states) {

            for (const std::string &k : j) {

                // If there is a resemblance between two parsed_sets combine the two sets
                if (std::find(parsed_set.begin(), parsed_set.end(), k) != parsed_set.end()) {

                    auto da = std::find(new_states.begin(), new_states.end(), j);
                    da->insert(da->end(), parsed_set.begin(), parsed_set.end());

                }
            }
            // Sort and erase duplicats
            std::sort(j.begin(), j.end());
            j.erase(unique(j.begin(), j.end()), j.end());
        }
        // Emplace parsed set vector in new_states
        new_states.emplace_back(parsed_set);
    }
}

void Utils::replace_states(DFA *old_dfa, DFA & minimized_DFA) {

    for (const std::string & symbol : old_dfa->get_alphabet()) {

        for (const std::pair<const std::string, State*> & i : old_dfa->get_states()) {

            std::string return_value;
            return_value = i.second->contains_set(minimized_DFA.get_states(), symbol);

            // State has a transition to a state set from minimized DFA
            if (return_value != "/") {
                std::string state_set = Utils::exist_set(minimized_DFA.get_states(), i.first);

                // State does not yet exist so make one
                if (state_set == "/") {

                    minimized_DFA.set_state(Utils::make_set({i.first}),
                                            i.second->get_starting(),
                                            i.second->get_accepting());

                    minimized_DFA.get_states().find(Utils::make_set({i.first}))->second->add_transition_duplicates(symbol,
                                                    minimized_DFA.get_states().find(return_value)->second);
                }
                else {
                    minimized_DFA.get_states().find(state_set)->second->add_transition_duplicates(symbol,
                                                    minimized_DFA.get_states().find(return_value)->second);

                }
            }
            else {
                minimized_DFA.set_state(Utils::make_set({i.first}),
                                        i.second->get_starting(),
                                        i.second->get_accepting());

                minimized_DFA.get_states().find(Utils::make_set({i.first}))->second->add_transition_duplicates(symbol,
                                                    minimized_DFA.get_states().find(return_value)->second);
            }
        }
    }

}

std::map<const std::string, Pair *> Utils::minimize_(DFA* dfa) {

    // Make pairs
    std::map<const std::string, Pair*> pairs = Pair::make_pairs(dfa);
    // Base case
    Utils::mark_accepting(pairs);

    // Recursive case
    Utils::mark_all(pairs, dfa);
    return pairs;
}
