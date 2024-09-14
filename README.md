# Automata Simulator (DFA & NFA) in C++

## Overview

This project implements both a **Deterministic Finite Automaton (DFA)** and a **Non-deterministic Finite Automaton (NFA)** simulator, written in C++. It allows users to define DFAs and NFAs using JSON format and visualize them using `.dot` files for further processing and visualization through tools like [Graphviz](https://graphviz.org/).

## Features

- Define and simulate both DFAs and NFAs using JSON input.
- Visualize automaton states and transitions via `.dot` files.
- Easily check whether a string is accepted by the DFA or NFA.
- NFA can be converted to DFA using the subset construction method.
- DFA minimization using the Hopcroft algorithm.
- Closure and transition functions for NFA.

## Project Structure

- **input_json/**: Directory containing DFA and NFA configurations in JSON format.
- **output_dot/**: Directory where `.dot` files are generated for visualization.
- **src/**: C++ source code for the automata simulator.
- **tests/**: (Optional) Unit tests for the automaton logic.
- **CMakeLists.txt**: Configuration file for building the project with CMake.

## Usage

1. **Input Example:** Here's an example of how a DFA and NFA are defined in JSON:

```json
{
  "type": "DFA",
  "alphabet": ["a", "e"],
  "states": [
    {
      "name": "1",
      "starting": false,
      "accepting": true
    },
    {
      "name": "3",
      "starting": false,
      "accepting": false
    },
    {
      "name": "2",
      "starting": false,
      "accepting": false
    },
    {
      "name": "0",
      "starting": true,
      "accepting": false
    },
    {
      "name": "4",
      "starting": false,
      "accepting": false
    }
  ],
  "transitions": [
    {
      "from": "1",
      "to": "2",
      "input": "e"
    },
    {
      "from": "1",
      "to": "3",
      "input": "a"
    },
    {
      "from": "0",
      "to": "1",
      "input": "e"
    },
    {
      "from": "0",
      "to": "4",
      "input": "a"
    },
    {
      "from": "4",
      "to": "4",
      "input": "e"
    },
    {
      "from": "4",
      "to": "4",
      "input": "a"
    },
    {
      "from": "2",
      "to": "3",
      "input": "e"
    },
    {
      "from": "2",
      "to": "4",
      "input": "a"
    },
    {
      "from": "3",
      "to": "2",
      "input": "e"
    },
    {
      "from": "3",
      "to": "2",
      "input": "a"
    }
  ]
}
```
2. **Generate Dot Files:** Use the DFA or NFA class in the program to generate .dot files:
```cpp
DFA dfa("input_json/DFA.json");
dfa.generate_dot();  // Creates a .dot file in output_dot/

NFA nfa("input_json/NFA.json");
nfa.generate_dot();  // Creates a .dot file in output_dot/
```

3. **Check if String is Accepted:** The DFA and NFA can be used to check whether a given string is accepted:
```cpp
cout << boolalpha << dfa.accepts("0010110100") << endl;  // For DFA
cout << boolalpha << nfa.accepts("0110") << endl;        // For NFA
```
