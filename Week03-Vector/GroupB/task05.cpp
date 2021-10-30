#include <iostream>
#include <vector>

template <typename T>
using filterFunc = bool(*)(T);

template <typename T>
std::vector<T> filter(std::vector<T>& myVector, filterFunc<T> myFunc)
{
    std::vector<T> result;
    for (T current : myVector)
    {
        if (myFunc(current))
        {
            result.push_back(current);
        }
    }

    return result;
}

template <typename T>
void printVector(std::vector<T> vector)
{
    for (T current : vector)
    {
        std::cout << current << " ";
    }
    std::cout << std::endl;
}

bool isEven(int number)
{
    return number % 2 == 0;
}

int main ()
{
    std::vector<int> myVector;
    myVector.push_back(1);
    myVector.push_back(5);
    myVector.push_back(6);
    myVector.push_back(2);
    myVector.push_back(0);

    printVector(filter(myVector, isEven));
    
    return 0;
}