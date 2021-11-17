#include <vector>
#include <iostream>

std::size_t getFirstLowerBuldingToTheLeft(const std::vector<int>& vector, std::size_t currentIndex) 
{
    std::size_t result = currentIndex;
    while (result != 0 && vector[result - 1] >= vector[currentIndex]) 
    {
        --result;
    }

    return result;
}

std::size_t getFirstLowerBuldingToTheRight(const std::vector<int>& vector, std::size_t currentIndex) 
{
    std::size_t result = currentIndex;
    while (result != vector.size() - 1 && vector[result + 1] >= vector[currentIndex]) 
    {
        ++result;
    }

    return result;
}

long largestRectangle(std::vector<int> h) 
{
    std::size_t size = h.size();
    long biggestArea = 0;
    
    for (size_t i = 0; i < size; ++i) 
    {
        size_t start = getFirstLowerBuldingToTheLeft(h, i);
        size_t end = getFirstLowerBuldingToTheRight(h, i);

        long currentArea = (end - start + 1) * h[i];
        if (currentArea > biggestArea) {
            biggestArea = currentArea;
        }
    }
    
    return biggestArea;
}



int main() 
{
    int input = 0;
    std::cin >> input;

    std::vector<int> heights;
    
    for (std::size_t i = 0; i < input; ++i) 
    {
        int n = 0;
        std::cin >> n;
        heights.push_back(n);
    }

    std::cout << largestRectangle(heights) << std::endl;
    
    return 0;
}





















