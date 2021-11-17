#include <iostream>

void primeFactorization(unsigned int number)
{
    unsigned int divisor = 2;
    while (number > 1)
    {
        while (number % divisor == 0)
        {
            std::cout << divisor << " ";
            number /= divisor;
        }

        ++divisor;
    }
    std::cout << std::endl;
}

int main ()
{
    primeFactorization(99);

    return 0;
}