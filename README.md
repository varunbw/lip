# lip
## Leetcode Input Parser

Currently parses all known (to me) inputs for Leetcode problems

# Installation

```bash
git clone https://github.com/varunbw/lip
cd lip
./run
```

`./run` will compile the library and the code generator if they're not present.

# Usage

There are a variety of parsing functions available to deal with the inputs Leetcode provides, but you need not call them manually. This project includes a code generator, which will look at the function signature you give it, and accordingly generate a ready-to-use file with the parsing code all done.

For example, consider the first Leetcode problem, `twoSum`:

1. Paste the empty solution function as-in, into [main.cpp](main.cpp), overwriting its defualt contents.
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
    }
};
```

2. Run `./generate`. (If this executable is missing, run `./run` to make it)

3. Done, the generator will parse the function signature, and produce this output
```cpp
#include "lib/lip.hpp" // all necessary headers already included

using namespace std; // only excusable for DSA

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
    }
};

int main(void) {

    ifstream fin("input.txt");
    Solution sol;

    while (fin.eof() == false) {
        vector<int> vec = Parse_Int1D(fin);
        int n  = Parse_Int(fin);

        println("{}", sol.twoSum(vec, n));
    }

    // No excess commented code for the other parsing functions

    return 0;
}
```

# Parsing

Here are all the parsing functions provided by the library.

### Basic data types + String:
```cpp
int n         = Parse_Int(fin);
float f       = Parse_Float(fin);
char c        = Parse_Char(fin);
bool b        = Parse_Bool(fin);
std::string s = Parse_String(fin);
```

### Arrays
Note: `fin` here is a `std::ifstream`
```cpp
using std::vector;
using std::string;

vector<int> vec    = Parse_Int1D(fin);
vector<char> vec   = Parse_Char1D(fin);
vector<string> vec = Parse_String1D(fin);
```

### Matrices
```cpp
using std::vector;
using std::string;

vector<vector<int>> vec    = Parse_Int2D(fin);
vector<vector<char>> vec   = Parse_Char2D(fin);
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


# Manual Input Parsing

If you don't like the generator and would rather do it yourself.

The parsing functions expect an input stream _reference_, to keep track of already parsed data. Simplest way to do it is already provided in [template.cpp](template.cpp); a file input stream; `std::ifstream`, parsing from `input.txt`.

In the common case of needing to parse two or more inputs, you need to call the parsing functions in the order that they appear in the input data.

For example, consider this example function:
```cpp
int Calculate(int k, vector<vector<int>> data, vector<string> queries);
```

The input data for all functions is provided in the order that the variables appear in the function signature. An example test suite would look like this.
```
4                           // plain int
[[1,2,3],[4,5,6]]           // 2D int vector
["query 1", "query 2"]      // 1D string vector
6
[[7,8,9,10],[11,12,13,14]]
["query 18", "query 12"]
```
First three lines are the first test case, next three are the second test case.

#### Don't actually put any comments like above in `input.txt`.

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

# Issues

Please open an issue if you find a bug with the code, or would like to propose new features.

### Format:
```
<Short title>
<Description of the issue>

<Text dump or a screenshot please>
<Any more information>
```

# Contributions & Issues

Please open a pull request if you'd like to submit changes to the code, thanks. I do have some guidelines, please refer to [CONTRIBUTING.md](CONTRIBUTING.md)