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

bool isBalanced(std::string s) 
{
    std::stack<char> brackets;
    
    for (char current : s) 
    {
        if (isBracketOpened(current)) 
        {
            brackets.push(current);
        }
        else if (isBracketClosed(current))
        {
            if (!brackets.empty() && doBracketsMatch(brackets.top(), current)) 
            {
                brackets.pop();
            }
            else 
            {
                return false;
            }
        }
    }

    if (!brackets.empty()) 
    {
        return false;
    }

    return true;
}

int main ()
{
    std::cout << std::boolalpha << isBalanced("(3+6) / {54g( p3[jw ][])}") << std::endl;
    std::cout << std::boolalpha << isBalanced("{(526)}[91]}") << std::endl;

    return 0;
}