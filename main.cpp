#include "lib/lip.hpp"

#include <print>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
    }
};

int main(void) {

    std::ifstream fin("input.txt");
    Solution sol;

    while (fin.eof() == false) {
		vector<int> var1 = Parse_Int1D(fin);
		int var2 = Parse_Int(fin);

		std::println("{}", sol.twoSum(var1, var2));
    }

    return 0;
}