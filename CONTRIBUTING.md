# Guidelines

In the extremely rare case that someone ever lays their eyes upon this project and decides to contribute, here are my potentially annoying code guidelines :P

- Open a pull request for the changes. Name your branch as a short description, in kebab-case (mmm kebab). ex: `improve-binary-tree-construction`.
- Please name your pull request appropriately, with an overview of the changes. (ex: "Improve binary tree constructions by eliminating redundant code")
- For naming conventions, please follow the rest of the codebase:

# Naming conventions

## Variable
camelCase (ex: `vectorSize`) 

Exceptions can be made when variables have numbers in their name which need to be separated for clarity.

## Function/Class/Namespace 
PascalCase (ex: `GraphNode`) 

Parsing functions are an exception to this, which become a combination of PascalCase and Snake_Case. I prefer the underscore there to provide more separation to the word "Parse" from what it parses. ex: I like `Parse_Vector2D` over `ParseVector2D`.

# Brace Placement
Please begin your curly braces for functions, classes, namespaces, `if`, `for`, etc. blocks on the same line as the statement
```cpp
if (s.size()) {
    return 0;
}

void Square(int x) {
    return x * x;
}
```

# Important
- Don't pollute the scope with indiscriminate `using` statements, and definitely no `using namespace std`. It's fine in the main solution file, but not in the library codebase.