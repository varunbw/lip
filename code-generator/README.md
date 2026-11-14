# Code generator

No this does not generate solutions for you by making calls to a LLM.

Code generator does the job of writing the parsing code for you, so you don't have to write it yourself.

Consider the first problem on leetcode:

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
    }
};
```

As you can see, it takes in two parameters; a `vector<int>`, and an `int`
Normally, you'd have to edit `main.cpp` yourself, and uncomment the necessary parsing lines in order for it to parse accordingly. That would look something like this:

```cpp
std::vector<int> vec = Parse_Int1D(fin);
int n         = Parse_Int(fin);

std::println("{}", sol.twoSum(vec, n));
```

You'll have to do this yourself for every problem that you're solving.

This generator aims to do it for you, by parsing the function signature, and accordingly generating the required code.

# Steps
1. Paste the empty solution function as-in, into [main.cpp](main.cpp)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
    }
};
```

2. Run `./generate`

3. Done, the generator will parse the function signature, and produce this output
```cpp
#include "lib/lip.hpp"

#include <fstream>
#include <print>

#include <vector> // only necessary headers included

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

That's it. It removes the headache of dealing with correct header includes as well.
Earlier, it was more convenient to just include every header so you don't have to deal with that as well, but that increases compile time slightly because the preprocessor pastes every file, which the compiler sits there and parses.