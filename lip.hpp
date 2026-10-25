#pragma once

#include <format>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
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
            "[ERROR]: Input stream not open"
        ));
    }

    if (fin.fail()) {
        throw std::runtime_error(MakeErrorMessage(
            "[ERROR]: Input stream failed"
        ));
    }

    if (fin.eof()) {
        throw std::runtime_error(MakeErrorMessage(
            "[ERROR]: Input stream at EOF, check testcases again"
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