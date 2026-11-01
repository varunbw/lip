#include "lib/lip.hpp"

#include <fstream>
#include <print>

using std::vector;
using std::string;

class Solution {
public:


};

int main(int argc, char** argv) {

    std::ifstream fin ("input.txt");
    std::ofstream fout("output.txt");

    std::println("Hello world! Press Ctrl-C to exit");

    while (fin.eof() == false) {

        Solution sol;

        // -- int
        // int n; fin >> n;
        // std::println("{}", sol.);

        // -- 1D int
        // std::vector<int> vec = Parse_Int1D(fin);
        // std::println("{}", sol.);

        // -- 2D int
        // std::vector<std::vector<int>> grid = Parse_Int2D(fin);
        // std::println("{}", sol.);

        // -- String
        // std::string s; fin >> s; s.erase(s.begin()); s.pop_back();
        // std::println("{}", sol.);
        
        // -- 1D string
        // std::vector<std::string> vec = Parse_String1D(fin);
        // std::println("{}", sol.);

        // -- 2D string
        // std::vector<std::vector<std::string>> grid = Parse_String2D(fin);
        // std::println("{}", sol.);

        // -- 1D char
        // std::vector<char> vec = Parse_Char1D(fin);
        // std::println("{}", sol.);

        // -- 2D char
        // std::vector<std::vector<char>> grid = Parse_Char2D(fin);
        // std::println("{}", sol.);

        // -- Linked List
        // LinkedList linkedList(Parse_Int1D(fin));
        // std::println("{}", sol.);

        // -- Binary Tree
        // BinaryTree binaryTree(Parse_String1D(fin));
        // std::println("{}", sol.);
    }

    return 0;
}