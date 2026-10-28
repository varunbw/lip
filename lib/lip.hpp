#pragma once

#include <format>
#include <fstream>
#include <string>
#include <utility>
#include <vector>


// -- Text Colors
#define BLACK_START "\033[30m"
#define RED_START "\033[31m"
#define GREEN_START "\033[32m"
#define YELLOW_START "\033[33m"
#define BLUE_START "\033[34m"
#define MAGENTA_START "\033[35m"
#define CYAN_START "\033[36m"
#define WHITE_START "\033[37m"
#define RESET_COLOR "\033[0m"


// -- Utility
template <typename... Args>
std::string MakeErrorMessage(std::format_string<Args...> err, Args&&... args) {
    return std::format(
        RED_START "[ERROR]: {}\n" RESET_COLOR,
        std::format(err, std::forward<Args>(args)...)
    );
}

// -- Parsers
void ValidateInputStream(std::ifstream& fin);
std::string GetLineFromStream(std::ifstream& fin);
std::vector<int> FileParse_Int1D(std::ifstream& fin);
std::vector<std::vector<int>> FileParse_Int2D(std::ifstream& fin);
std::vector<std::string> FileParse_String1D(std::ifstream& fin);
std::vector<std::vector<std::string>> FileParse_String2D(std::ifstream& fin);
std::vector<char> FileParse_Char1D(std::ifstream& fin);
std::vector<std::vector<char>> FileParse_Char2D(std::ifstream& fin);

// -- Linked List
struct ListNode {
    int val;
    ListNode* next;

    ListNode();
    ListNode(int x);
    ListNode(int x, ListNode* next);
};

class LinkedList {
    
    ListNode* head;
    void Print(const ListNode* node) const;
    void DeleteNode(ListNode* node);
    
public:

    LinkedList(const std::vector<int>& nodes);
    ~LinkedList();
    
    ListNode* GetFirst() const;
    void SetFirst(ListNode* value);
    void Print() const;
};


// -- Binary Tree
struct TreeNode {
    int val;
    TreeNode* left;

    TreeNode* right;
    TreeNode();
    TreeNode(int x);
};

class BinaryTree {

    TreeNode* root;

    void PrintPreOrder(const TreeNode* node) const;
    void PrintInOrder(const TreeNode* node) const;
    void PrintPostOrder(const TreeNode* node) const;
    void DeleteNode(TreeNode* node);

public:

    BinaryTree(const std::vector<std::string>& nodes);
    ~BinaryTree();

    TreeNode* GetRoot() const;
    void SetRoot(TreeNode* value);

    void PrintPreOrder() const;
    void PrintInOrder() const;
    void PrintPostOrder() const;
    void PrintLevelOrder() const;
};
