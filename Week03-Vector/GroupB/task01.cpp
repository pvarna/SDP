#include <iostream>
#include <vector>

template <typename T>
typename std::vector<T>::iterator findElement(std::vector<T>& myVector, T elem)
{
    for (typename std::vector<T>::iterator it = myVector.begin(); it != myVector.end(); ++it)
    {
        if (*it == elem)
        {
            return it;
        }
    }

    return myVector.end();
}

int main ()
{
    std::vector<std::string> myVector;
    myVector.push_back("Armyanov");
    myVector.push_back("Semerdjiev");
    myVector.push_back("Kalin");
    myVector.push_back("Trifon");

    std::vector<std::string>::iterator result = findElement<std::string>(myVector, "Armyanov");
    std::cout << *result << std::endl;

    std::vector<std::string>::iterator end = findElement<std::string>(myVector, "Nora");
    std::cout << std::boolalpha << (end == myVector.end()) << std::endl;

    return 0;
}