# DFA-simulator-cpp

DFA simulator made for automata course using cpp. DFA's can be edited using ```.json``` files and visualized
using ```.dot``` files. The projects is still being updated so there can be some bugs or features that are yet
to be completed. I hope you enjoy it!

## Usage

Make sure to set your working directory to ```input_json``` or any other directory that has correctly formatted
 ```.json``` files in it. All the ```.dot``` files are store in the ```output_dot``` directory and can be visualized
 using [magjac](http://magjac.com/graphviz-visual-editor/) for example or any other .dot editor.
 
All DFA's must be formatted correctly. Here is a small example:

```json
{
  "type": "DFA",
  "alphabet": [
    "0",
    "1"
  ],
  "states": [
    {
      "name": "Q0",
      "starting": true,
      "accepting": false
    },
    {
      "name": "Q1",
      "starting": false,
      "accepting": true
    },
    {
      "name": "Q2",
      "starting": false,
      "accepting": false
    }
  ],
  "transitions": [
    {
      "from": "Q0",
      "to": "Q0",
      "input": "0"
    },
    {
      "from": "Q0",
      "to": "Q1",
      "input": "1"
    },
    {
      "from": "Q1",
      "to": "Q1",
      "input": "0"
    },
    {
      "from": "Q1",
      "to": "Q0",
      "input": "1"
    }
  ]
}
``` 
 
```cpp
DFA dfa("DFA.json"); // Create new DFA, .json file will be automatically parsed.
dfa.generate_dot(); // Generate .dot file, will be placed in output_dot directory.
cout << boolalpha << dfa.accepts("0010110100") << endl; // Check whether this string is accepted by the DFA.
```

## License
[MIT](https://choosealicense.com/licenses/mit/)