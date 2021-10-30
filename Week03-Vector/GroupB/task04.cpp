#include <iostream>
#include <vector>

template <typename T>
using changeElementFunc = void(*)(T&);

template <typename T>
void apply(std::vector<T>& myVector, changeElementFunc<T> myFunc)
{
    for (T current : myVector)
    {
        myFunc(current);
        std::cout << current << " ";
    }
    std::cout << std::endl;
}

void square(int& number)
{
    number *= number;
}

int main ()
{
    std::vector<int> myVector;
    myVector.push_back(1);
    myVector.push_back(5);
    myVector.push_back(6);
    myVector.push_back(2);
    myVector.push_back(0);
    
    apply(myVector, square);
    return 0;
}