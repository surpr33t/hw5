#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(
    std::string& current,
    int index,
    std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& result
);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result;

    string current = in;

    helper(current, 0, floating, dict, result);

    return result;
}

// Define any helper functions here
void helper(
    string& current,
    int index,
    string floating,
    const set<string>& dict,
    set<string>& result
)
{
    //base case
    if(index == (int)current.size())
    {
        if(floating.empty() && dict.find(current) != dict.end())
        {
            result.insert(current);
        }
        return;
    }

    //fixed letter case
    if(current[index] != '-')
    {
        helper(current, index + 1, floating, dict, result);
        return;
    }

    //try all letters
    for(char c = 'a'; c <= 'z'; c++)
    {
        string newFloating = floating;

        size_t pos = newFloating.find(c);
        if(pos != string::npos)
        {
            newFloating.erase(pos, 1);
        }

        current[index] = c;

        helper(current, index + 1, newFloating, dict, result);

        current[index] = '-'; // backtrack
    }
}