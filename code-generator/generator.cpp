#include <algorithm>
#include <cstddef>
#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <vector>


struct SolutionInformation {
    std::string rawSolution{};
    std::string functionName{};
    std::string returnType{};
    std::vector<std::string> argumentsType{};
};

namespace Parser {

    SolutionInformation DeduceTypes(std::ifstream& in) {

        SolutionInformation res;
        
        struct {
            bool publicToken{};
            bool returnType{};
            bool firstArgument{};
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
                res.returnType = token;

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

                res.functionName = token.substr(0, openBracketPos);

                res.argumentsType.push_back(token.substr(openBracketPos + 1));
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

            res.argumentsType.push_back(token);
            tokenIsDataType = false;
        }
        
        // Don't really care about references, we just want the underlying
        // type to know what to parse
        std::ranges::for_each(res.argumentsType, [] (std::string& s) {
            if (s.back() == '&') {
                s.pop_back();
            }
        });

        return res;
    }
}


namespace Print {
    void FullFile(std::ofstream& out, SolutionInformation& info);
    void Includes(std::ofstream& out);
    void Solution(std::ofstream& out, SolutionInformation& info);
    void MainFunction(std::ofstream& out, SolutionInformation& info);
    void ExecutionLoop(std::ofstream& out, SolutionInformation& info);

    void FullFile(std::ofstream& out, SolutionInformation& info) {
        Print::Includes(out);
        Print::Solution(out, info);
        Print::MainFunction(out, info);
    }

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

    void Solution(std::ofstream& out, SolutionInformation& info) {
        out << info.rawSolution;
    }

    void MainFunction(std::ofstream& out, SolutionInformation& info) {

        const std::string mainFunction = 
            "int main(void) {\n"
            "\n"
            "   std::ifstream fin(\"input.txt\");\n"
            "   Solution sol\n"
            "\n"
            "   while (fin.eof() == false) {\n";

        out << mainFunction;

        ExecutionLoop(out, info);

        const std::string mainFunctionEnding =
            "   }\n"
            "   return 0;\n"
            "}";

        out << mainFunctionEnding;
    }

    void ExecutionLoop(std::ofstream& out, SolutionInformation& info) {
        
        const std::map<std::string, std::string_view> typeToCodeMap = {
            {"int",    "int {} = Parse_Int(fin);"},
            {"float",  "float {} = Parse_Float(fin);"},
            {"char",   "char {} = Parse_Char(fin);"},
            {"bool",   "bool {} = Parse_Bool(fin);"},
            {"string", "std::string {} = Parse_String(fin);"},

            {"vector<int>",    "vector<int> {} = Parse_Int1D(fin);"},
            {"vector<char>",   "vector<char> {} = Parse_Char1D(fin);"},
            {"vector<string>", "vector<string> {} = Parse_String1D(fin);"},

            {"vector<vector<int>>",    "vector<vector<int>> {} = Parse_Int2D(fin);"},
            {"vector<vector<char>>",   "vector<vector<char>> {} = Parse_Char2D(fin);"},
            {"vector<vector<string>>", "vector<vector<string>> {} = Parse_String2D(fin);"},

            {"ListNode*", "LinkedList {}(Parse_Int1D(fin));"},
            {"TreeNode*", "BinaryTree {}(Parse_String1D(fin));"},
        };

        int argumentCount = 0;

        for (const std::string& argType : info.argumentsType) {

            const std::string variableName = std::format(
                "var{}", ++argumentCount
            );

            // No runtime format in C++23 so we doing this shit by hand
            std::string callLine = std::string(typeToCodeMap.at(argType));
            const size_t bracketPos = callLine.find('{');
            callLine.replace(bracketPos, 2, variableName);

            std::println("Call line: {}", callLine);

            out << "\t\t"
                << callLine
                << "\n";
        }

        std::string argumentsSerialized = "";
        for (int i = 0; i < argumentCount; i++) {
            const std::string argument = std::format(
                "var{}",
                i + 1
            );
            argumentsSerialized.append(argument + ", ");
        }
        argumentsSerialized.pop_back();
        argumentsSerialized.pop_back();

        const std::string functionCall = std::format(
            "{}({})",
            info.functionName,
            argumentsSerialized
        );

        out << "\n" 
            << std::format(
                "\t\tstd::println(\"{}\", sol.{})\n",
                "{}", //  for these ^^ braces
                functionCall
            );
    }
}



int main(void) {

    std::ifstream fin("temp.cpp");

    SolutionInformation info = Parser::DeduceTypes(fin);
    std::println("{}", info.argumentsType);

    std::ofstream out("main-out.cpp");
    Print::FullFile(out, info);
    
    return 0;
}