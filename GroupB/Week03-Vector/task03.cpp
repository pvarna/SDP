#include <iostream>
#include <vector>

template <typename T>
bool doesContain(std::vector<T>& first, std::vector<T>& second)
{
    for (T current : second)
    {
        bool found = false;
        for (T currentFirst : first)
        {
            if (current == currentFirst)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return false;
        }
    }

    return true;
}

int main ()
{
    std::vector<int> first;
    first.push_back(1);
    first.push_back(5);
    first.push_back(6);
    first.push_back(2);
    first.push_back(0);

    std::vector<int> second;
    second.push_back(0);
    second.push_back(5);
    second.push_back(1);

    std::cout << std::boolalpha << doesContain(first, second) << std::endl;
    
    return 0;
}