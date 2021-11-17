#include <iostream>
#include <string>
#include <stack>

bool isBracketOpened(char ch) 
{
    return ch == '(' || ch == '[' || ch == '{';
}

bool isBracketClosed(char ch) 
{
    return ch == ')' || ch == ']' || ch == '}';
}

bool doBracketsMatch(char opened, char closed) 
{
    return (opened == '(' && closed == ')') 
        || (opened == '[' && closed == ']') 
        || (opened == '{' && closed == '}');
             
}

std::string isBalanced(std::string s) 
{
    std::stack<char> brackets;
    
    for (char current : s) 
    {
        if (isBracketOpened(current)) 
        {
            brackets.push(current);
        }
        else 
        {
            if (!brackets.empty() && doBracketsMatch(brackets.top(), current)) 
            {
                brackets.pop();
            }
            else 
            {
                return "NO";
            }
        }
    }

    if (!brackets.empty()) 
    {
        return "NO";
    }

    return "YES";
}

int main () 
{
    std::cout << isBalanced("{[()]}") << std::endl;
    std::cout << isBalanced("{[(])}") << std::endl;
    std::cout << isBalanced("{{[[(())]]}}") << std::endl;

    return 0;
}