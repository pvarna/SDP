#include <iostream>
#include <string>
#include <stack>

std::string getReverseString(const std::string& string)
{
    std::stack<char> characters;
    std::string result = "";

    for (char current : string)
    {
        characters.push(current);
    }

    while (!characters.empty())
    {
        result += characters.top();
        characters.pop();
    }

    return result;
}

int main ()
{
    std::cout << getReverseString("Stacks are cool!") << std::endl;
    return 0;
}