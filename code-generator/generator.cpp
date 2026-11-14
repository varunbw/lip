#include <algorithm>
#include <cstddef>
#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <vector>


namespace Parser {

    std::vector<std::string> DeduceTypes(std::ifstream& in) {

        std::vector<std::string> res;

        struct {
            bool publicToken = false;
            bool returnType = false;
            bool firstArgument = false;
        } seen;

        bool tokenIsDataType = false;

        while (in.eof() == false) {

            std::string token;
            in >> token;
            
            std::println("`{}`", token);

            if (seen.publicToken == false) {
                if (token != "public:") {
                    continue;
                }

                seen.publicToken = true;
                continue;
            }

            if (seen.returnType == false) {
                res.push_back(token);

                seen.returnType = true;
                continue;
            }

            if (seen.firstArgument == false) {
                // This token will be the return type

                // This token will be have the first argument
                const size_t openBracketPos = token.find('(');
                if (openBracketPos == std::string::npos) {
                    continue;
                }

                res.push_back(token.substr(openBracketPos + 1));
                seen.firstArgument = true;
                continue;
            }

            if (token == "{") {
                break;
            }
            if (tokenIsDataType == false) {
                tokenIsDataType = true;
                continue;
            }

            res.push_back(token);
            tokenIsDataType = false;
        }
        
        // Don't really care about references, we just want the underlying
        // type to know what to parse
        std::ranges::for_each(res, [] (std::string& s) {
            if (s.back() == '&') {
                s.pop_back();
            }
        });

        return res;
    }
}


namespace Print {
    void Includes(std::ofstream& out);
    void ParsingLoop(std::ofstream& out, std::vector<std::string>& dataTypes);
    void MainFunction(std::ofstream& out, std::vector<std::string>& dataTypes);

    void Includes(std::ofstream& out) {

        const std::string includes = 
            "#include \"lib/lip.hpp\"\n"
            "\n"
            "#include <fstream>\n"
            "#include <print>\n"
            "\n"
            "using namespace std;\n"
            "\n";

        out << includes;
    };

    void MainFunction(std::ofstream& out, std::vector<std::string>& parsingTypes) {

        const std::string mainFunction = 
            "int main(void) {\n"
            "\n"
            "   std::ifstream fin(\"input.txt\");\n"
            "   Solution sol\n"
            "\n"
            "   while (fin.eof() == false) {\n"
            "\n";

        out << mainFunction;

        ParsingLoop(out, parsingTypes);

        const std::string mainFunctionEnding =
            "   }\n"
            "   return 0;\n"
            "}";

        out << mainFunctionEnding;
    }

    void ParsingLoop(std::ofstream& out, std::vector<std::string>& dataTypes) {
        
        const std::map<std::string, std::string> typeToCodeMap = {
            {"int",    "int n         = Parse_Int(fin);"},
            {"float",  "float f       = Parse_Float(fin);"},
            {"char",   "char c        = Parse_Char(fin);"},
            {"bool",   "bool b        = Parse_Bool(fin);"},
            {"string", "std::string s = Parse_String(fin);"},
            {"vector<int>",    "vector<int> vec    = Parse_Int1D(fin);"},
            {"vector<char>",   "vector<char> vec   = Parse_Char1D(fin);"},
            {"vector<string>", "vector<string> vec = Parse_String1D(fin);"},
            {"vector<vector<int>>",    "vector<vector<int>> vec    = Parse_Int2D(fin);"},
            {"vector<vector<char>>",   "vector<vector<char>> vec   = Parse_Char2D(fin);"},
            {"vector<vector<string>>", "vector<vector<string>> vec = Parse_String2D(fin);"},
            {"ListNode*", "LinkedList list(Parse_Int1D(fin));"},
            {"TreeNode*", "BinaryTree tree(Parse_String1D(fin));"},
        };



    }
}



int main(void) {

    std::ifstream fin("temp.cpp");

    std::vector<std::string> types = Parser::DeduceTypes(fin);
    std::println("{}", types);

    std::ofstream out("main-out.cpp");
    Print::Includes(out);
    Print::MainFunction(out, types);
    
    return 0;
}