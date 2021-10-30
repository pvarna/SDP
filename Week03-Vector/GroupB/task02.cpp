#include <iostream>
#include <vector>

template <typename T>
std::vector<T> getReversedVector(std::vector<T>& myVector)
{
    std::vector<T> result = myVector;
    size_t size = myVector.size();
    
    for (size_t i = 0; i < size/2; --i)
    {
        std::swap(result.at(i), result.at(size - 1 - i));
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

int main ()
{
    std::vector<int> myNumbers;
    myNumbers.push_back(1);
    myNumbers.push_back(2);
    myNumbers.push_back(3);
    myNumbers.push_back(4);
    myNumbers.push_back(5);

    printVector(myNumbers);
    printVector(getReversedVector(myNumbers));
    
    return 0;
}
