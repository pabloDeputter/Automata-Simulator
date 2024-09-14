# DFA Automata Simulator

## Overview
This project implements a **Deterministic Finite Automaton (DFA) and NFA Simulator** written in C++. It was created as part of the Automata course to model and simulate DFAs. The simulator allows users to define DFAs using JSON format and visualize them using `.dot` files for further processing and visualization using tools like [Graphviz](https://graphviz.org/).

## Features
- Define and simulate DFAs using JSON input.
- Visualize DFA states and transitions via `.dot` files.
- Easily check whether a string is accepted by the DFA.
- Modular and extensible design for future enhancements.

## Project Structure
- **input_json/**: Directory containing DFA configurations in JSON format.
- **output_dot/**: Directory where `.dot` files are generated for visualization.
- **src/**: C++ source code for the DFA simulator.
- **tests/**: (Optional) Unit tests for the DFA logic.
- **CMakeLists.txt**: Configuration file for building the project with CMake.

## Usage
1**Input Example**: Here's an example of how a DFA is defined in JSON:
```json
   {
   "type":"DFA",
   "alphabet":[
      "0",
      "1"
   ],
   "states":[
      {
         "name":"Q0",
         "starting":true,
         "accepting":false
      },
      {
         "name":"Q1",
         "starting":false,
         "accepting":true
      },
      {
         "name":"Q2",
         "starting":false,
         "accepting":false
      }
   ],
   "transitions":[
      {
         "from":"Q0",
         "to":"Q0",
         "input":"0"
      },
      {
         "from":"Q0",
         "to":"Q1",
         "input":"1"
      },
      {
         "from":"Q1",
         "to":"Q1",
         "input":"0"
      },
      {
         "from":"Q1",
         "to":"Q0",
         "input":"1"
      }
   ]
   }
```
4. **Output Visualization**: Use the DFA class in the program to generate ```.dot``` files:
5. **Check String Acceptance**: You can check whether a string is accepted by the DFA using the ```accepts()``` method:
      ```cpp
   cout << boolalpha << dfa.accepts("0010110100") << endl;
   ```
