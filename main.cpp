#include "parser/lip.hpp"

using namespace std;

class Solution {
public:
    TreeNode* minimizeSum(TreeNode* root) {
        return root;
    }
};

int main(void) {

    std::ifstream fin("input.txt");
    Solution sol;

    while (fin.eof() == false) {
		BinaryTree var0(Parse_String1D(fin));
        var0.PrintInOrder();

		BinaryTree returnResult({"1"});
		returnResult.SetRoot(sol.minimizeSum(var0.GetRoot()));
		returnResult.PrintPreOrder();
    }

    return 0;
}