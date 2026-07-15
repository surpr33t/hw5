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
    const string& in,
    string current,
    int index,
    string floating,
    const set<string>& dict,
    set<string>& answers
);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> answers;
    string current = in;

    helper(in, current, 0, floating, dict, answers);

    return answers;

}

// Define any helper functions here
void helper(
    const string& in,
    string current,
    int index,
    string floating,
    const set<string>& dict,
    set<string>& answers
)
{
    //base case
    if(index == (int)in.size())
    {
        if(floating.empty() && dict.find(current) != dict.end())
        {
            answers.insert(current);
        }
        return;
    }

    //fixed letter
    if(in[index] != '-')
    {
        current[index] = in[index];
        helper(in, current, index + 1, floating, dict, answers);
    }
    else
    {
        //count remaining blanks
        int blanks = 0;
        for(int i = index; i < (int)in.size(); i++)
        {
            if(in[i] == '-') blanks++;
        }

        for(char c = 'a'; c <= 'z'; c++)
        {
            current[index] = c;

            string newFloating = floating;

            size_t pos = floating.find(c);
            if(pos != string::npos)
            {
                newFloating.erase(pos, 1);
            }
            else
            {
                if((int)floating.size() == blanks)
                {
                    continue;
                }
            }

            helper(in, current, index + 1, newFloating, dict, answers);
        }
    }
}
