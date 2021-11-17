#include <iostream>
#include <stack>

std::stack<int> getSortedStack(std::stack<int> source)
{
    std::stack<int> result;
    while (!source.empty())
    {
        int temp = source.top();
        source.pop();

        while (!result.empty() && result.top() < temp)
        {
            source.push(result.top());
            result.pop();
        }
        result.push(temp);
    }

    return result;
}

int main ()
{
    std::stack<int> s;
    s.push(4);
    s.push(3);
    s.push(8);
    s.push(5);
    s.push(-2);
    s.push(0);
    s.push(12);

    std::stack<int> sSorted = getSortedStack(s);
    while (!sSorted.empty())
    {
        std::cout << sSorted.top() << " ";
        sSorted.pop();
    }
    std::cout << std::endl;

    return 0;
}