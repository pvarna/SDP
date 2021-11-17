#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>

double doCalculation(double a, double b, char operation)
{
    switch (operation)
    {
    case '+':
        return a + b;

    case '-':
        return a - b;

    case '*':
        return a * b;

    case '/':
        return a / b;
    
    case '^':
        return std::pow(a, b);
    }

    return 0.0;
}

double postfixCalculator(std::string expression)
{
    std::stack<int> values;
    for (char current : expression)
    {
        if (isdigit(current))
        {
            values.push(current - '0');
        }
        else
        {
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();

            values.push(doCalculation(a, b, current));
        }
    }

    return values.top();
}


int main ()
{
    std::cout << postfixCalculator("62+") << std::endl;
    std::cout << postfixCalculator("437+*2/") << std::endl;

    return 0;
}