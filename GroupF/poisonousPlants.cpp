#include <vector>
#include <iostream>

std::vector<int> getDescendingSubvectorFrom(const std::vector<int>& vector, std::size_t index, std::size_t& endIndex)
{
    std::vector<int> result;
    result.push_back(vector[index]);
    std::size_t size = vector.size();

    for (std::size_t i = index + 1; i < size; ++i)
    {
        if (vector[i] > vector[i-1])
        {
            endIndex = i;
            return result;
        }
        result.push_back(vector[i]);
    }
    endIndex = size;

    return result;
}

void vectorAppend(std::vector<int>& result, const std::vector<int>& toAppend)
{
    result.insert(result.end(), toAppend.begin(), toAppend.end());
}

void removeHeadsOfSubvectors(std::vector<std::vector<int>>& subvectors)
{
    std::size_t subvectorSize = subvectors.size();
    for (std::size_t i = subvectorSize - 1; i >= 1; --i)
    {
        if (subvectors[i].front() > subvectors[i-1].back())
        {
            subvectors[i].erase(subvectors[i].begin());
        }
    }
}

void removeEmptyVectors(std::vector<std::vector<int>>& subvectors)
{
    int subvectorSize = subvectors.size();
    for (int i = subvectorSize - 1; i >= 0; --i)
    {
        if (subvectors[i].empty())
        {
            subvectors.erase(subvectors.begin() + i);
        }
    }
}

void mergeSuccessiveVectorsIfDescending(std::vector<std::vector<int>>& subvectors)
{
    std::size_t subvectorSize = subvectors.size();
    for (std::size_t i = subvectorSize - 1; i >= 1; --i)
    {
        if (subvectors[i].front() <= subvectors[i-1].back())
        {
            vectorAppend(subvectors[i-1], subvectors[i]);

            subvectors.erase(subvectors.begin() + i);
        }
    }
}

int poisonousPlants(std::vector<int> p) 
{
    std::vector<std::vector<int>> descendingSubvectors;
    std::size_t endIndex = 0;
    
    std::size_t pSize = p.size();
    while (endIndex != pSize)
    {
        int currentStart = endIndex;
        descendingSubvectors.push_back(getDescendingSubvectorFrom(p, currentStart, endIndex));
    }
    
    std::size_t days = 0;
    
    while (descendingSubvectors.size() > 1)
    {
        removeHeadsOfSubvectors(descendingSubvectors);

        removeEmptyVectors(descendingSubvectors);

        mergeSuccessiveVectorsIfDescending(descendingSubvectors);

        ++days;
    }

    return days;
}

// 3 6 2 7 5
// 6 5 8 4 2 7 10 9 12

int main ()
{
    std::vector<int> v1;
    v1.push_back(3);
    v1.push_back(6);
    v1.push_back(2);
    v1.push_back(7);
    v1.push_back(5);

    std::vector<int> v2;
    v2.push_back(6);
    v2.push_back(5);
    v2.push_back(8);
    v2.push_back(4);
    v2.push_back(2);
    v2.push_back(7);
    v2.push_back(10);
    v2.push_back(9);
    v2.push_back(12);

    std::cout << poisonousPlants(v1) << std::endl;
    std::cout << poisonousPlants(v2) << std::endl;

    return 0;
}