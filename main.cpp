#include "lip.hpp"

#include <fstream>
#include <print>

class Solution {
public:


};

int main(int argc, char** argv) {

    std::ifstream fin ("input.txt");
    std::ofstream fout("output.txt");

    while (fin.eof() == false) {

        Solution sol;

        // -- int
        // int n; fin >> n;
        // std::println("{}", sol.);

        // -- 1D int
        // std::vector<int> vec = FileParse_Int1D(fin);
        // std::println("{}", sol.);

        // -- 2D int
        // std::vector<std::vector<int>> grid = FileParse_Int2D(fin);
        // std::println("{}", sol.);

        // -- String
        // std::string s; fin >> s; s.erase(s.begin()); s.pop_back();
        // std::println("{}", sol.);
        
        // -- 1D string
        // std::vector<std::string> vec = FileParse_String1D(fin);
        // std::println("{}", sol.);

        // -- 2D string
        // std::vector<std::vector<std::string>> grid = FileParse_String2D(fin);
        // std::println("{}", sol.);

        // -- 1D char
        // std::vector<char> vec = FileParse_Char1D(fin);
        // std::println("{}", sol.);

        // -- 2D char
        // std::vector<std::vector<char>> grid = FileParse_Char2D(fin);
        // std::println("{}", sol.);

        // -- Linked List
        // LinkedList linkedList(FileParse_Int1D(fin));
        // std::println("{}", sol.);

        // -- Binary Tree
        // BinaryTree binaryTree(FileParse_String1D(fin));
        // std::println("{}", sol.);
    }

    return 0;
}