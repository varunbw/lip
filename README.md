# lip
## Leetcode Input Parser

Currently parses all known (to me) inputs for Leetcode problems

# Installation

```bash
git clone https://github.com/varunbw/lip
cd lip
./run
```

The run script will compile the library if its not present (which it won't be on the first run)

In order to make a new library if you make some changes to the library code, run
```bash
./run clean
```

`clean` option will recompile the library

# Parsing

### Basic data types:
```cpp
int n; fin >> n;
float f; fin >> f;
char c; fin >> c;
bool b; fin >> b;
```

### String
Slightly more effort because each test case string is wrapped in double quotes, so we need to get rid of those
```cpp
std::string s; fin >> s; s.erase(s.begin()); s.pop_back();
```

### Arrays
Note: `fin` here is a `std::ifstream`
```cpp
using std::vector;
using std::string;

vector<int> vec = Parse_Int1D(fin);
vector<char> vec = Parse_Char1D(fin);
vector<string> vec = Parse_String1D(fin);
```

### Matrices
```cpp
using std::vector;
using std::string;

vector<vector<int>> vec = Parse_Int2D(fin);
vector<vector<char>> vec = Parse_Char2D(fin);
vector<vector<string>> vec = Parse_String2D(fin);
```

### Linked Lists
Linked list are serialized into arrays when giving input, the `LinkedList` constructor expects a 1D int vector
```cpp
LinkedList list(Parse_Int1D(fin));
```

### Binary Tree
Binary Trees are also serialized into arrays when giving input, the `BinaryTree` constructor expects a 1D string vector
```cpp
BinaryTree tree(Parse_String1D(fin));
```


# Input

The parsing functions expect an input stream _reference_, to keep track of already parsed data. Simplest way to do it is already provided in [main.cpp](main.cpp); a file input stream; `std::ifstream`, parsing from `input.txt`. Feel free to change the file name in the code.

In the common case of needing to parse two or more inputs, you need to call the parsing functions in the order that they appear in the input data

For example, consider this example function:
```cpp
int Calculate(int k, vector<vector<int>> data, vector<string> queries);
```

The input data for all functions is provided in the order that the variables appear in the function signature. An example test suite would look like this
```
4                           // plain int
[[1,2,3],[4,5,6]]           // 2D int vector
["query 1", "query 2"]      // 1D string vector
6
[[7,8,9,10],[11,12,13,14]]
["query 18", "query 12"]
```
First three lines are the first test case, next three are the second test case.

The parsing code for this would look like
```cpp
int k; fin >> k;
vector<vector<int>> data = Parse_Int2D(fin);
vector<string> queries = Parse_String1D(fin);

std::println("{}", sol.Calculate(k, data, queries));
```

`k` first, then `data`, then `queries`

Since these lines are in a loop, it'll run till the input file is over
```cpp
while (fin.eof()) {
    // Parsing code
}
```
