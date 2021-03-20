#include "src/DFA.h"
#include "src/Utils.h"

using namespace std;

// TODO - EQUAL OPERATOR DFA MOET HETZELFDE BLIJVEN
// TOOD - print moet in .json format

//int main() {
//    DFA dfa("input-tfa2.json");
////    DFA mindfa = dfa.minimize();
//    dfa.printTable();
//    return 0;
//}

int main() {

    DFA dfa1("input-eq1.json");
    DFA dfa2("input-eq2.json");
    cout << boolalpha << (dfa1 == dfa2) << endl;

    return 0;
}
