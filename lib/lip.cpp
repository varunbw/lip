#include "lip.hpp"

#include <cstddef>
#include <print>
#include <queue>
#include <stdexcept>
#include <sstream>

// -- Parsers
/*
    @brief Perform basic error checking on the input string
    @param
    `fin` The input file stream
    
    `callerFuncName` The name of the function to print in error messages
    @return None
*/
void ValidateInputStream(std::ifstream& fin) {
    if (fin.is_open() == false) {
        throw std::runtime_error(MakeErrorMessage(
            "Input stream not open"
        ));
    }

    if (fin.fail()) {
        throw std::runtime_error(MakeErrorMessage(
            "Input stream failed"
        ));
    }

    if (fin.eof()) {
        throw std::runtime_error(MakeErrorMessage(
            "Input stream at EOF, check testcases again"
        ));
    }
}

std::string GetLineFromStream(std::ifstream& fin) {

    std::string res;

    // Remove any newline character left in the buffer
    if (fin.peek() == '\n')
        fin.ignore();
    
    std::getline(fin, res);

    return res;
}

/*
    @brief Parse inputs into a vector<int> from the given stream `fin`
    @param `fin` The input file stream
    @return Parsed input in a vector<int>

    This works with the following format only:
        [1,2,3,4,...]
*/
std::vector<int> FileParse_Int1D(std::ifstream& fin) {

    ValidateInputStream(fin);

    std::string line = GetLineFromStream(fin);

    // Erase any leading/trailing brackets that ideally should be there
    if (line[0] == '[')
        line.erase(line.begin());
    if (line.back() == ']')
        line.pop_back();

    std::vector<int> res;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, ',')) {
        while (item.size() && item[0] == ' ')
            item.erase(item.begin());

        try {
            res.push_back(std::stoi(item));
        }
        catch (std::invalid_argument err) {
            throw std::runtime_error(MakeErrorMessage(
                "Tried to convert {} to int",
                item
            ));
        }
    }
    
    return res;
}


/*
    @brief Parse inputs into a vector<vector<int>> from the given stream `fin`
    @param `fin` The input file stream
    @return Parsed input in a vector<vector<int>>

    This works with the following format only:
        [[1,2,3,4,...],[5,6,7,8,...],...]
*/
std::vector<std::vector<int>> FileParse_Int2D(std::ifstream& fin) {

    ValidateInputStream(fin);
    std::string line = GetLineFromStream(fin);

    // Erase any leading/trailing brackets that ideally should be there
    if (line[0] == '[')
        line.erase(line.begin());
    if (line.back() == ']')
        line.pop_back();

    std::vector<std::vector<int>> res;
    std::stringstream ssOuter(line);
    std::string itemOuter;

    // Outer loop fetches one row at a time
    while (std::getline(ssOuter, itemOuter, ']')) {
        if (itemOuter[0] == ',')
            itemOuter.erase(itemOuter.begin());

        std::vector<int> row;
        std::stringstream ssInner(itemOuter);
        std::string itemInner;

        // Inner loop processes each element
        while (std::getline(ssInner, itemInner, ',')) {
            while (itemInner[0] == '[' || itemInner[0] == ' ')
                itemInner.erase(itemInner.begin());

            try {
                row.push_back(std::stoi(itemInner));
            }
            catch (std::invalid_argument err) {
                throw std::runtime_error(MakeErrorMessage(
                    "Tried to convert {} to int",
                    itemInner
                ));
            }
        }
        
        res.push_back(row);
    }
    
    return res;
}


/*
    @brief Parse inputs into a vector<string> from the given stream `fin`
    @param `fin` The input file stream
    @return Parsed input in a vector<string>

    Wrap your strings with "", this function works with the following format only:
        ["Hello","World"]

    Refer FAQs on why more formats aren't supported
*/
std::vector<std::string> FileParse_String1D(std::ifstream& fin) {

    ValidateInputStream(fin);
    std::string line = GetLineFromStream(fin);

    if (line[0] == '[')
        line.erase(line.begin());
    if (line.back() == ']')
        line.pop_back();

    std::vector<std::string> res;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, ',')) {
        // Remove any whitespace
        while (item.size() && item[0] == ' ')
            item.erase(item.begin());
        
        // Remove starting and ending "s
        if (item.size() && item[0] == '"')
            item.erase(item.begin());
        if (item.back() == '"')
            item.pop_back();

        res.push_back(item);
    }

    return res;
}


/*
    @brief Parse inputs into a vector<vector<string>> from the given stream `fin`
    @param `fin` The input file stream
    @return Parsed input in a vector<vector<string>>

    Wrap your strings with "", this function works with the following format only:
        [["Hello","World"],["This is ", "a test"]]
    
    You may leave spaces here anywhere, but in case you dont see the expected output, just stick to no spaces

    Refer FAQs on why more formats aren't supported
*/
std::vector<std::vector<std::string>> FileParse_String2D(std::ifstream& fin) {

    ValidateInputStream(fin);
    std::string line = GetLineFromStream(fin);

    if (line[0] == '[')
        line.erase(line.begin());
    if (line.back() == ']')
        line.pop_back();

    std::vector<std::vector<std::string>> res;
    std::stringstream ssOuter(line);
    std::string itemOuter;

    while (std::getline(ssOuter, itemOuter, ']')) {
        if (itemOuter[0] == ',')
            itemOuter.erase(itemOuter.begin());

        std::vector<std::string> row;
        std::stringstream ssInner(itemOuter);
        std::string itemInner;

        while(std::getline(ssInner, itemInner, ',')) {
            // Remove any opening brackets and whitespaces that the item might have
            while (itemInner.size() && (itemInner[0] == '[' || itemInner[0] == ' '))
                itemInner.erase(itemInner.begin());

            // Remove the "" that a string is encased in
            if (itemInner.size() && itemInner[0] == '"')
                itemInner.erase(itemInner.begin());
            if (itemInner.back() == '"')
                itemInner.pop_back();

            row.push_back(itemInner);  
        }
        
        res.push_back(row);
    }

    return res;
}


/*
    @brief Parse inputs into a vector<char> from the given stream `fin`
    @param `fin` The input file stream
    @return Parsed input in a vector<char>

    Wrap your chars with "", this function works with the following format only:
        ["a","b","c","d","e"]

    You may leave spaces here anywhere, but in case you dont see the expected output, just stick to no spaces

    Refer FAQs on why more formats aren't supported
*/
std::vector<char> FileParse_Char1D(std::ifstream& fin) {

    ValidateInputStream(fin);
    std::string line = GetLineFromStream(fin);

    // Erase any leading/trailing brackets that ideally should be there
    if (line[0] == '[')
        line.erase(line.begin());
    if (line.back() == ']')
        line.pop_back();
    
    std::vector<char> res;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, ',')) {
        // Erase any spaces from the beginning
        while (item.size() && item[0] == ' ')
            item.erase(item.begin());

        // Remove the "" that a character is encased in
        if (item.size() && item[0] == '"')
            item.erase(item.begin());
        if (item.back() == '"')
            item.pop_back();
        
        // Warn user if element is more than 1 letter long
        const size_t itemSize = item.size();
        if (itemSize != 1) {
            throw std::runtime_error(MakeErrorMessage(
                "Item {} is of size {} when expected size is 1",
                item, itemSize
            ));
        }

        // Add the 0th element of item, which happens to be the entire thing
        res.push_back(item[0]);
    }

    return res;
}


/*
    @brief Parse inputs into a vector<vector<char>> from the given stream `fin`
    @param `fin` The input file stream
    @return Parsed input in a vector<vector<char>>

    Wrap your chars with "", this function works with the following format only:
        [["a","b","c","d","e"],['a','b','c','d','e']]
        [[a,b,c,d,e],[a,b,c,d,e]]

    You may leave spaces here anywhere, but in case you dont see the expected output, just stick to one of the above formats

    Refer FAQs on why more formats aren't supported
*/
std::vector<std::vector<char>> FileParse_Char2D(std::ifstream& fin) {

    ValidateInputStream(fin);
    std::string line = GetLineFromStream(fin);

    // Erase any leading/trailing brackets that should be 
    if (line[0] == '[')
        line.erase(line.begin());
    if (line.back() == ']')
        line.pop_back();

    std::vector<std::vector<char>> res;
    std::stringstream ssOuter(line);
    std::string itemOuter;

    // Outer loop processes takes a row at a time
    while (getline(ssOuter, itemOuter, ']')) {
        if (itemOuter.size() && itemOuter[0] == ',')
            itemOuter.erase(itemOuter.begin());

        std::vector<char> row;
        std::stringstream ssInner(itemOuter);
        std::string itemInner;

        // Inner loop processes individual elements
        while (std::getline(ssInner, itemInner, ',')) {
            while (itemInner.size() && (itemInner[0] == ' ' || itemInner[0] == '['))
                itemInner.erase(itemInner.begin());
            
            // Remove any leading/trailing "s
            if (itemInner.size() && itemInner[0] == '"')
                itemInner.erase(itemInner.begin());
            if (itemInner.back() == '"')
                itemInner.pop_back();

            // Warn user if element is more than 1 letter long
            const size_t itemSize = itemInner.size();

            if (itemSize != 1) {
                throw std::runtime_error(MakeErrorMessage(
                    "Item {} is of size {} when expected size is 1",
                    itemInner, itemSize
                ));
            }

            row.push_back(itemInner[0]);
        }

        res.push_back(row);
    }

    return res;
}



// -- Linked List
ListNode::ListNode(int x) :
    val(x),
    next(nullptr)
{}

ListNode::ListNode(int x, ListNode* next) :
    val(x),
    next(next)
{}

LinkedList::LinkedList(const std::vector<int>& nodes) {

    if (nodes.empty()) {
        throw std::runtime_error(MakeErrorMessage("Empty vector passed as argument"));
    }

    this->head = new ListNode(nodes[0]);
    ListNode* prev = head;
    
    const size_t n = nodes.size();
    for (size_t i = 1; i < n; i++) {
        ListNode* newNode = new ListNode(nodes[i]);
        prev->next = newNode;
        prev = newNode;
    }
}

LinkedList::~LinkedList() {
    DeleteNode(head);
}

void LinkedList::DeleteNode(ListNode* node) {

    if (node == nullptr) {
        return;
    }

    DeleteNode(node->next);
    delete node;
}

void LinkedList::Print(const ListNode* node) const {

    if (node == nullptr) {
        return;
    }

    std::print("{}, ", node->val);
    Print(node->next);
}

void LinkedList::Print() const {
    this->Print(this->head);
    std::println("");
}


// -- Binary Tree
TreeNode::TreeNode(int val) :
    val(val),
    left(nullptr),
    right(nullptr)
{}

/*
    @brief Constructs a binary tree out of the given vector
    @param nodes The representation of nodes
    @return Root of tree

    Leetcode uses BFS to serialize binary trees into a string.
    ex:   1
         / \
        2   3
           / \
          4   5
    
    gets serialized into "[1,2,3,null,null,4,5]"

    * Check comment in source code for clearer visual representation
*/
BinaryTree::BinaryTree(const std::vector<std::string>& nodes) {

    if (nodes.empty() || nodes[0] == "null") {
        throw std::runtime_error(MakeErrorMessage("Empty vector passed as argument"));
    }

    this->root = new TreeNode(std::stoi(nodes[0]));

    // Use a queue to build the tree level by level
    std::queue<TreeNode*> queue;
    queue.push(this->root);

    int i = 1;
    while (queue.empty() == false && i < nodes.size()) {

        TreeNode* curr = queue.front();
        queue.pop();

        // Process the left child
        if (nodes[i] != "null") {
            TreeNode* leftNode = new TreeNode(std::stoi(nodes[i]));
            curr->left = leftNode;
            queue.push(leftNode);
        }
        i++;

        // Process the right child
        if (i < nodes.size() && nodes[i] != "null") {
            TreeNode* rightNode = new TreeNode(std::stoi(nodes[i]));
            curr->right = rightNode;
            queue.push(rightNode);
        }
        i++;
    }
}

BinaryTree::~BinaryTree() {
    DeleteNode(this->root);
}

void BinaryTree::DeleteNode(TreeNode* node) {

    if (node == nullptr) {
        return;
    }

    DeleteNode(node->left);
    DeleteNode(node->right);

    delete node;
}

TreeNode* BinaryTree::GetRoot() const {
    return this->root;
}

void BinaryTree::SetRoot(TreeNode* value) {
    this->root = value;
}

void BinaryTree::PrintPreOrder(const TreeNode* node) const {

    if (node == nullptr) {
        return;
    }

    std::print("{}, ", node->val);
    PrintPreOrder(node->left);
    PrintPreOrder(node->right);
}

void BinaryTree::PrintPreOrder() const {
    this->PrintPreOrder(this->root);
    std::println("");
}

void BinaryTree::PrintInOrder(const TreeNode* node) const {

    if (node == nullptr) {
        return;
    }

    PrintInOrder(node->left);
    std::print("{}, ", node->val);
    PrintInOrder(node->right);
}

void BinaryTree::PrintInOrder() const {
    this->PrintInOrder(this->root);
    std::println("");
}

void BinaryTree::PrintPostOrder(const TreeNode* node) const {

    if (node == nullptr) {
        return;
    }

    PrintPostOrder(node->left);
    PrintPostOrder(node->right);
    std::print("{}, ", node->val);
}

void BinaryTree::PrintPostOrder() const {
    this->PrintPostOrder(this->root);
    std::println("");
}

void BinaryTree::PrintLevelOrder() const {

    if (this->root == nullptr) {
        return;
    }

    std::queue<const TreeNode*> queue;
    queue.push(this->root);

    while (queue.size()) {
        const TreeNode* curr = queue.front();
        queue.pop();

        std::print("{}, ", curr->val);

        if (curr->left) {
            queue.push(curr->left);
        }
        if (curr->right) {
            queue.push(curr->right);
        }
    }

    std::println("");
}
