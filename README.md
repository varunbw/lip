# lip
## Leetcode Input Parser

Does what the name says.

Currently parses all known (to me) inputs for Leetcode problems:
### Basic data types:
```cpp
int n; fin >> n;
float f; fin >> f;
char c; fin >> c;
bool b; fin >> b;
```

### Arrays
```cpp
vector<int> vec = Parse_Int1D(fin);
vector<char> vec = Parse_String1D(fin);
vector<std::string> vec = Parse_String1D(fin);
```


