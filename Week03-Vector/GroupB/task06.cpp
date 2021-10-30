#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
typename std::vector<T>::iterator findKthLargest(std::vector<T>& myVector, int k)
{
    size_t size = myVector.size();
    if (k < 1 || k > size)
    {
        throw std::invalid_argument("invalid k");
    }

    std::vector<T> temp = myVector;

    for (size_t i = 0; i < k; ++i)
    {
        size_t currentMaxIndex = i;
        for (size_t j = i; j < size; ++j)
        {
            if (temp[j] > temp[currentMaxIndex])
            {
                currentMaxIndex = j;
            }
        }
        std::swap(temp[i], temp[currentMaxIndex]);
    }

    T resultValue = temp[k-1];
    for (size_t i = 0; i < size; ++i)
    {
        if (myVector[i] == resultValue)
        {
            return myVector.begin() + i;
        }
    }

    return myVector.end();
}

int main ()
{
    std::vector<int> myVector;
    myVector.push_back(0);
    myVector.push_back(2);
    myVector.push_back(4);
    myVector.push_back(6);
    myVector.push_back(8);
    myVector.push_back(10);
    myVector.push_back(12);

    std::cout << *findKthLargest(myVector, 5) << std::endl;
    return 0;
}